#pragma once
#include "Utilities.h"
namespace BM
{
    template<typename T>
    class CORE_DLL Singleton
    {
    protected:
        Singleton()
        {
            BM_Assert(msInstance == NULL);
            msInstance = static_cast<T*>(this);
        }

        virtual ~Singleton()
        {
            BM_Assert(msInstance == static_cast<T*>(this));
            msInstance = NULL;
        }

    public:
        static T& Instance()
        {
            BM_Assert(msInstance != NULL);
            return *msInstance;
        }

        static T* InstancePtr()
        {
            return msInstance;
        }

        static void CreateInstance()
        {
            new T();
        }

        static void DeleteInstance()
        {
            SAFE_DELETE(msInstance);
        }

    protected:
        static T* msInstance;
    };
}

// Work with Singleton template class.
// Put this in cpp file.
#define BM_SINGLETON_IMPLEMENT(T)   template<> T* Singleton<T>::msInstance = NULL


//////////////////////////////////////////////////////////////////////////
// Macros to define singleton.
#define SINGLETON_DECLARE(T)                                            \
    public:                                                             \
        static void CreateInstance()                                    \
        {                                                               \
            BM_Assert(msInstance == NULL);                             \
            msInstance = new T();                                      \
        }                                                               \
        static void DeleteInstance()                                    \
        {                                                               \
            if (msInstance != NULL)                                    \
            {                                                           \
                delete msInstance;                                     \
                msInstance = NULL;                                     \
            }                                                           \
        }                                                               \
        static T* GetInstance()                                         \
        {                                                               \
            BM_Assert(msInstance != NULL);                             \
            return msInstance;                                         \
        }                                                               \
    private:                                                            \
        static T* msInstance

#define SINGLETON_DEFINE(T) T* T::msInstance
//////////////////////////////////////////////////////////////////////////
