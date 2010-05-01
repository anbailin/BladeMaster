#pragma once

namespace BM
{
    template<typename T>
    class CORE_DLL Singleton
    {
    protected:
        Singleton()
        {
            BM_Assert(s_pInstance == NULL);
            s_pInstance = static_cast<T*>(this);
        }

        virtual ~Singleton()
        {
            BM_Assert(s_pInstance == static_cast<T*>(this));
            s_pInstance = NULL;
        }

    public:
        static T& Instance()
        {
            BM_Assert(s_pInstance != NULL);
            return *s_pInstance;
        }

        static T* InstancePtr()
        {
            return s_pInstance;
        }

        static void CreateInstance()
        {
            new T();
        }

        static void DeleteInstance()
        {
            SafeDelete(s_pInstance);
        }

    protected:
        static T* s_pInstance;
    };
}

// Work with Singleton template class.
// Put this in cpp file.
#define BM_SINGLETON_IMPLEMENT(T)   template<> T* Singleton<T>::s_pInstance = NULL


//////////////////////////////////////////////////////////////////////////
// Macros to define singleton.
#define BM_SINGLETON_DECLARE(T)                                         \
    public:                                                             \
        static void CreateInstance()                                    \
        {                                                               \
            BM_Assert(s_pInstance == NULL);                             \
            s_pInstance = new T();                                      \
        }                                                               \
        static void DeleteInstance()                                    \
        {                                                               \
            if (s_pInstance != NULL)                                    \
            {                                                           \
                delete s_pInstance;                                     \
                s_pInstance = NULL;                                     \
            }                                                           \
        }                                                               \
        static T& Instance()                                            \
        {                                                               \
            BM_Assert(s_pInstance != NULL);                             \
            return *s_pInstance;                                        \
        }                                                               \
        static T* InstancePtr()                                         \
        {                                                               \
            return s_pInstance;                                         \
        }                                                               \
    private:                                                            \
        static T* s_pInstance

#define BM_SINGLETON_DEFINE(T) T* T::s_pInstance
//////////////////////////////////////////////////////////////////////////
