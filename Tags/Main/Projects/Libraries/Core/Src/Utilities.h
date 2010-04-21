// Included in CorePublic.h

//////////////////////////////////////////////////////////////////////////
// Assert
#define BM_Assert(test)     Q_ASSERT(test)
#define BM_AssertHr(hr)     BM_Assert(((HRESULT)(hr)) >= 0);
//////////////////////////////////////////////////////////////////////////

namespace BM
{
    template<typename T>
    inline void SafeRelease(T& p)
    {
        if (p != NULL)
        {
            p->Release();
            p = NULL;
        }
    }

    template<typename T>
    inline void SafeDelete(T& p)
    {
        if (p != NULL)
        {
            delete p;
            p = NULL;
        }
    }

    template<typename T>
    inline void SafeDeleteArray(T& p)
    {
        if (p != NULL)
        {
            delete[] p;
            p = NULL;
        }
    }
}