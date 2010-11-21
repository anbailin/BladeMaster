#include "CorePrivate.h"
#include "DataBreakPoint.h"


int FindBreakpointIndexForAddress(const void* address, CONTEXT& ctx, DWORD** retDebugReg)
{
    int dataIndex(-1);
    *retDebugReg = 0;

    if (ctx.Dr0 == (size_t)address)
    {
        dataIndex = 0;
        *retDebugReg = &ctx.Dr0;
    }
    else if (ctx.Dr1 == (size_t)address)
    {
        dataIndex = 1;
        *retDebugReg = &ctx.Dr1;
    }
    else if (ctx.Dr2 == (size_t)address)
    {
        dataIndex = 2;
        *retDebugReg = &ctx.Dr2;
    }
    else if (ctx.Dr3 == (size_t)address)
    {
        dataIndex = 3;
        *retDebugReg = &ctx.Dr3;
    }
    return dataIndex;
}

int FindFreeBreakpointIndex(CONTEXT& ctx, DWORD** retDebugReg)
{
    return FindBreakpointIndexForAddress(NULL, ctx, retDebugReg);
}

// Indexed with DataBreakpoint::Enum
const u32 triggerMasks[] =
{
    0xFFFFFFFF, // NONE
    1,			// WRITE
    3,			// READWRITE
    0,			// EXECUTE
};

// Indexed with DataBreakpoint::SizeEnum
const u32 sizeMasks[] =
{
    0, 1, 3, 2,
};

u32 GetSizeMask(u32 size)
{
    switch(size)
    {
    case 1:return 0;
    case 2:return 1;
    case 4:return 3;
    case 8:return 2;        
    }
    return 0xffffffff;
}

bool SetDataBreakpoint(const void* address, BPAccessType accessType, u32 dataSize)
{
    CONTEXT threadContext;
    threadContext.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    const HANDLE currentThread = ::GetCurrentThread();
    if (!::GetThreadContext(currentThread, &threadContext))
    {
        return false;
    }

    DWORD* dataDebugReg(0);
    int dataIndex = FindBreakpointIndexForAddress(address, threadContext, &dataDebugReg);
    bool success(false);
    
    // Clear data breakpoint
    if (accessType == EBT_None)
    {
        if (dataIndex >= 0)
        {
            threadContext.Dr7 &= ~(3 << (dataIndex * 2));
            *dataDebugReg = 0;	// clear address
            success = true;
        }
    }
    else	// set/change data breakpoint
    {
        if (dataIndex < 0)
        {
            dataIndex = FindFreeBreakpointIndex(threadContext, &dataDebugReg);
        }

        if (dataIndex >= 0)
        {
            // Enable breakpoint.
            threadContext.Dr7 &= ~(3 << (dataIndex * 2));
            threadContext.Dr7 |= 3 << (dataIndex * 2);	// local & global

            // Set trigger mode.
            // (starts at bit 16, 2 bits per entry).
            const u32 triggerMask = accessType;
            threadContext.Dr7 &= ~(3 << ((dataIndex * 2) + 16)); // clear old mask
            threadContext.Dr7 |= triggerMask << ((dataIndex * 2) + 16);

            // Set data size
            // (starts at bit 24, 2 bits per entry).
            threadContext.Dr7 &= ~(3 << ((dataIndex * 2) + 24)); // clear old mask
            const u32 sizeMask = GetSizeMask(dataSize);
            threadContext.Dr7 |= sizeMask << ((dataIndex * 2) + 24);

            *dataDebugReg = (DWORD)((size_t)address);

            success = true;
        }
    }

    if (success)
    {
        success = (::SetThreadContext(currentThread, &threadContext) != 0);
    }

    return success;
}    