#pragma once

//#include "Core.h"

namespace BM
{
    class CORE_DLL ClassFactory
    {
        BM_CLASS_NO_COPY(ClassFactory);

    public:
        typedef void* (*ClassCreateFunc) (void*);

    public:
        static bool  Register(const String& name, ClassCreateFunc func);
        static void* CreateInstance(const String& name, void* buffer = NULL);

    private:
        static QHash<String, ClassCreateFunc> s_Creators;
    };
}

//////////////////////////////////////////////////////////////////////////
// Macros to register class in ClassFactory.
// Put this outside the class declaration.
#define BM_CLASS_FACTORY_REGISTER(_Class_)                              \
    static void* ClassFactoryCreate_##_Class_(void* buffer)             \
    {                                                                   \
        if (buffer) return new (buffer) _Class_();                      \
        else return new _Class_();                                      \
    }                                                                   \
    static const bool ClassFactoryRegister_##_Class_ = ::BM::ClassFactory::Register(#_Class_, ClassFactoryCreate_##_Class_)
