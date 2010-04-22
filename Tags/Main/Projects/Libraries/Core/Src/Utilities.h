// Included in CorePublic.h

//////////////////////////////////////////////////////////////////////////
// Assert
#define BM_Assert(test)     Q_ASSERT(test)
#define BM_AssertHr(hr)     BM_Assert(((HRESULT)(hr)) >= 0)
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Delete & Release
namespace BM
{
    template<typename T> inline void SafeDelete(T& p)      { if (p != 0) { delete p;     p = 0; } }
    template<typename T> inline void SafeDeleteArray(T& p) { if (p != 0) { delete[] p;   p = 0; } }
    template<typename T> inline void SafeRelease(T& p)     { if (p != 0) { p->Release(); p = 0; } }
}
//////////////////////////////////////////////////////////////////////////
