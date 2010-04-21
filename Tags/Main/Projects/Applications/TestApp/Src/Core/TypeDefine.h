#ifndef CORE_TYPEDEFINE_H
#define CORE_TYPEDEFINE_H

typedef char			s8;
typedef unsigned char	u8;
typedef short			s16;
typedef unsigned short	u16;
typedef long			s32;
typedef unsigned long	u32;
typedef long long		s64;
typedef unsigned long long u64;
typedef int				sword;
typedef unsigned int	word;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef char				int8;
typedef short				int16;
typedef int					int32;
typedef long long			int64;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif


#ifndef SUCCEEDED
#define SUCCEEDED(Status) ((HRESULT)(Status) >= 0)
#endif

#ifndef FAIL_ASSERT
#define FAIL_ASSERT(status) assert(SUCCEEDED(status));
#endif

//#ifdef CORE_EXPORT_DLL
//#define CORE_DLL __declspec( dllexport )
//#else
//#define CORE_DLL __declspec( dllimport )
//#endif
//
//#ifdef UTIL_EXPORT_DLL
//#define UTIL_DLL __declspec( dllexport )
//#else
//#define UTIL_DLL __declspec( dllimport )
//#endif
//
//#ifdef RENDER_EXPORT_DLL
//#define RENDER_DLL __declspec( dllexport )
//#else
//#define RENDER_DLL __declspec( dllimport )
//#endif
//
//#ifdef ANIM_EXPORT_DLL
//#define ANIM_DLL __declspec( dllexport )
//#else
//#define ANIM_DLL __declspec( dllimport )
//#endif
//
//#ifdef FILESYS_EXPORT_DLL
//#define FILESYS_DLL __declspec( dllexport )
//#else
//#define FILESYS_DLL __declspec( dllimport )
//#endif
//
//#ifdef ENGINE_EXPORTS
//#define ENGINE_DLL __declspec( dllexport )
//#else
//#define ENGINE_DLL __declspec( dllimport )
//#endif

#define CORE_DLL
#define UTIL_DLL
#define RENDER_DLL
#define ANIM_DLL
#define FILESYS_DLL
#define ENGINE_DLL

#define SINGLETON_DECLARE(type)		static type* mInstance; \
    static void CreateInstance()    { assert(mInstance==NULL); mInstance = new type; } \
    static void DestroyInstance()   {delete mInstance; mInstance = NULL; }\
    static type* GetInstance()      { return mInstance; } \

#define SINGLETON_DEFINE(type)		type* type::mInstance;

#endif //CORE_TYPEDEFINE_H