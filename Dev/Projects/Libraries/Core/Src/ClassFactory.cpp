#include "CorePrivate.h"
#include "BMString.h"
#include "ClassFactory.h"

namespace BM
{
    QHash<QString, ClassFactory::ClassCreateFunc> ClassFactory::s_Creators;

    bool ClassFactory::Register(const QString& name, ClassCreateFunc func)
    {        
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

    void* ClassFactory::CreateInstance(const QString& name, void* buffer)
    {        
        ClassCreateFunc func = s_Creators.value(name);
        BM_Assert(func != NULL);

        return (*func)(buffer);
    }
}
