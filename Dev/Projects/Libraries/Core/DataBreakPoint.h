#pragma once

enum BPAccessType
{
    EBT_None = 0xFFFFFFFF,
    EBT_Write = 1,
    EBT_ReadWrite = 3,
    EBT_Execute = 0
};

bool SetDataBreakpoint(const void* address, BPAccessType accessType, u32 dataSize);