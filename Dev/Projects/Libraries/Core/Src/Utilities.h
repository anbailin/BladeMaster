//////////////////////////////////////////////////////////////////////////
// Assert
#define BM_Assert(test)                     assert(test)
//#define BM_AssertMsg(test, where, what)     Q_ASSERT_X(test, where, what)
#define BM_AssertHr(hr)                     BM_Assert(((HRESULT)(hr)) >= 0)
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Macro to disable class copy constructor and asign opertaion.
#define BM_CLASS_NO_COPY(T)                                             \
    private:                                                            \
        T (const T&);                                                   \
        const T& operator = (const T&)
//////////////////////////////////////////////////////////////////////////

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif
