#include "CorePrivate.h"
#include "ClassFactory.h"

namespace BM
{
    QHash<String, ClassFactory::ClassCreateFunc> ClassFactory::s_Creators;

    bool ClassFactory::Register(const String& name, ClassCreateFunc func)
    {
        BM_Assert(name != NULL);
        BM_Assert(func != NULL);

        if (s_Creators.contains(name))
        {
            //if (s_Creators.value(name) != func)
            //{
            //    BM_Assert(0);
            //}
            return false;
        }
        else
        {
            s_Creators.insert(name, func);
            return true;
        }
    }

    void* ClassFactory::CreateInstance(const String& name, void* buffer)
    {
        BM_Assert(name != NULL);

        ClassCreateFunc func = s_Creators.value(name);
        BM_Assert(func != NULL);

        return (*func)(buffer);
    }
}
