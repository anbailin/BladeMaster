#pragma once

#include "CorePublic.h"

namespace BM
{
    template<typename T>
    class CORE_API Singleton
    {
    protected:
        Singleton()
        {
            BM_Assert(s_Instance == NULL);
            s_Instance = static_cast<T*>(this);
        }

        virtual ~Singleton()
        {
            BM_Assert(s_Instance == static_cast<T*>(this));
            s_Instance = NULL;
        }

    public:
        static T& Instance()
        {
            BM_Assert(s_Instance != NULL);
            return *s_Instance;
        }

        static T* InstancePtr()
        {
            return s_Instance;
        }

        static void CreateInstance()
        {
            new T();
        }

        static void DeleteInstance()
        {
            SafeDelete(s_Instance);
        }

    protected:
        static T* s_Instance;
    };
}

// Work with Singleton template class.
// Put this in cpp file.
#define BM_SINGLETON_IMPLEMENT(T)   template<> T* Singleton<T>::s_Instance = NULL


//////////////////////////////////////////////////////////////////////////
// Macros to define singleton.
#define BM_SINGLETON_DECLARE(T)             \
    public:                                 \
        static void CreateInstance()        \
        {                                   \
            BM_Assert(s_Instance == NULL);  \
            s_Instance = new T();           \
        }                                   \
        static void DeleteInstance()        \
        {                                   \
            if (s_Instance != NULL)         \
            {                               \
                delete s_Instance;          \
                s_Instance = NULL;          \
            }                               \
        }                                   \
        static T& Instance()                \
        {                                   \
            BM_Assert(s_Instance != NULL);  \
            return *s_Instance;             \
        }                                   \
        static T* InstancePtr()             \
        {                                   \
            return s_Instance;              \
        }                                   \
    protected:                              \
        static T* s_Instance;

#define BM_SINGLETON_DEFINE(T)              \
    T* T::s_Instance;
//////////////////////////////////////////////////////////////////////////
