
#define SINGLETON_DECLARE(type)		static type* mInstance; \
									static void CreateInstance()    { assert(mInstance==NULL); mInstance = new type; } \
                                    static void DestroyInstance()   {delete mInstance; mInstance = NULL; }\
									static type* GetInstance()      { return mInstance; } \

#define SINGLETON_DEFINE(type)		type* type::mInstance;