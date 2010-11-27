#pragma once

#include "Utilities.h"


class CORE_DLL ClassFactory
{
    BM_CLASS_NO_COPY(ClassFactory);

public:
    typedef void* (*ClassCreateFunc) (void*);

public:
    static bool  Register(const QString& name, ClassCreateFunc func);
    static void* CreateInstance(const QString& name, void* buffer = NULL);

private:
    static QHash<QString, ClassCreateFunc> s_Creators;
};


//////////////////////////////////////////////////////////////////////////
// Macros to register class in ClassFactory.
// Put this outside the class declaration.
#define BM_CLASS_FACTORY_REGISTER(_Class_)                              \
    static void* ClassFactoryCreate_##_Class_(void* buffer)             \
{                                                                   \
    if (buffer) return new (buffer) _Class_();                      \
        else return new _Class_();                                      \
}                                                                   \
    static const bool ClassFactoryRegister_##_Class_ = ::ClassFactory::Register(#_Class_, ClassFactoryCreate_##_Class_)
