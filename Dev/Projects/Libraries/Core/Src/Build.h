//////////////////////////////////////////////////////////////////////////
// Configurations
#if defined(DEBUG) || defined(_DEBUG)
#   define BM_DEBUG         1
#elif defined(NDEBUG)
#   define BM_RELEASE       1
#else
#   error "Invalid Configuration"
#endif
//////////////////////////////////////////////////////////////////////////

//dll define:
#ifdef CORE_EXPORT_DLL
#define CORE_DLL __declspec( dllexport )
#else
#define CORE_DLL __declspec( dllimport )
#endif

#ifdef UTIL_EXPORT_DLL
#define UTIL_DLL __declspec( dllexport )
#else
#define UTIL_DLL __declspec( dllimport )
#endif

#ifdef RENDER_EXPORT_DLL
#define RENDER_DLL __declspec( dllexport )
#else
#define RENDER_DLL __declspec( dllimport )
#endif

#ifdef ANIM_EXPORT_DLL
#define ANIM_DLL __declspec( dllexport )
#else
#define ANIM_DLL __declspec( dllimport )
#endif

#ifdef FILESYS_EXPORT_DLL
#define FILESYS_DLL __declspec( dllexport )
#else
#define FILESYS_DLL __declspec( dllimport )
#endif

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL __declspec( dllexport )
#else
#define ENGINE_DLL __declspec( dllimport )
#endif

