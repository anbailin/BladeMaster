//////////////////////////////////////////////////////////////////////////
// Assert
#define BM_Assert(test)                     Q_ASSERT(test)
#define BM_AssertMsg(test, where, what)     Q_ASSERT_X(test, where, what)
#define BM_AssertHr(hr)                     BM_Assert(((HRESULT)(hr)) >= 0)
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

//////////////////////////////////////////////////////////////////////////
// Macro to disable class copy constructor and asign opertaion.
#define BM_CLASS_NO_COPY(T)                                             \
    private:                                                            \
        T (const T&);                                                   \
        const T& operator = (const T&)
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Macros to declare singleton.
#define BM_CLASS_DECLARE_SINGLETON(T)                                                                           \
    BM_CLASS_NO_COPY(T);                                                                                        \
    public:                                                                                                     \
        static T& Instance()                                                                                    \
        {                                                                                                       \
            BM_AssertMsg(s_pInstance != (T*)0,  #T"::Instance()", "Use singleton before its being created!");   \
            BM_AssertMsg(s_pInstance != (T*)-1, #T"::Instance()", "Use singleton after it has been deleted!");  \
            return *s_pInstance;                                                                                \
        }                                                                                                       \
        static T* InstancePtr()                                                                                 \
        {                                                                                                       \
            return s_pInstance;                                                                                 \
        }                                                                                                       \
        static void CreateInstance()                                                                            \
        {                                                                                                       \
            BM_Assert(s_pInstance == 0);                                                                        \
            s_pInstance = new T();                                                                              \
        }                                                                                                       \
        static void DeleteInstance()                                                                            \
        {                                                                                                       \
            if (s_pInstance != 0 && s_pInstance != (T*)-1)                                                      \
            {                                                                                                   \
                delete s_pInstance;                                                                             \
                s_pInstance = 0;                                                                                \
            }                                                                                                   \
        }                                                                                                       \
    private:                                                                                                    \
        T()                                                                                                     \
        {                                                                                                       \
            s_pInstance = this;                                                                                 \
            Constructor();                                                                                      \
        }                                                                                                       \
        ~T()                                                                                                    \
        {                                                                                                       \
            Destructor();                                                                                       \
            s_pInstance = (T*)-1;                                                                               \
        }                                                                                                       \
        void Constructor();                                                                                     \
        void Destructor();                                                                                      \
    private:                                                                                                    \
        static T* s_pInstance

#define BM_CLASS_IMPLEMENT_SINGLETON(T) T* T::s_pInstance = 0
//////////////////////////////////////////////////////////////////////////
