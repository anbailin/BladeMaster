#include "CorePrivate.h"
#include "ClassFactory.h"

namespace BM
{
    QHash<const char*, ClassFactory::ClassCreateFunc> ClassFactory::s_Creators;

    bool ClassFactory::Register(const char* name, ClassCreateFunc func)
    {
        BM_Assert(func != NULL);
        BM_Assert(name != NULL);

        if (s_Creators.contains(name))
        {
            if (s_Creators.value(name) != func)
            {
                BM_Assert(0);
            }
            return false;
        }
        else
        {
            s_Creators.insert(name, func);
            return true;
        }
    }

    void* ClassFactory::CreateInstance(const char* name)
    {
        if (name == NULL || !s_Creators.contains(name))
        {
            return NULL;
        }

        ClassCreateFunc func = s_Creators.value(name);
        return (*func)(0);
    }

    void* ClassFactory::CreateInstance(const char* name, void* buffer)
    {
        if (name == NULL || buffer == NULL || !s_Creators.contains(name))
        {
            return NULL;
        }

        ClassCreateFunc func = s_Creators.value(name);
        return (*func)(buffer);
    }
}
