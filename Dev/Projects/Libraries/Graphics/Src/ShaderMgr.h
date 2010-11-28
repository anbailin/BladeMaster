#pragma once

/*
 *	upper 32 bit for shader type information, can't do bit operation
 *	lower 32 bit for shader macro, can do bit operation for macro combination
 */
typedef u64 ShaderId;
#define InvalidShaderTypeId 0xffffffff00000000
#define InvalidShaderMacroId 0x00000000ffffffff
#define InvalidShaderId 0xffffffffffffffff

/*
 *	store shader pair(vs,ps), and the intermediate data
 */
struct ShaderHandle
{
    ShaderHandle():mPreprocessShaderCrc(0),mVSCompiledSrcCrc(0),mPSCompiledSrcCrc(0){} 
    VertexShaderPtr  mVertexShader;
    PixelShaderPtr   mPixelShader;
    TArray<u8>       mPreprocessShader;    
    TArray<u8>       mVSCompiledShader;
    TArray<u8>       mPSCompiledShader;
    u32              mPreprocessShaderCrc;    
    u32              mVSCompiledSrcCrc;
    u32              mPSCompiledSrcCrc;
};

/*
 *	shader description, information stored in the corresponding xml files
 */
struct ShaderDesc
{
    BMStr                   name;
    TArray<BMStr>           definitions;
    TArray<ShaderId>        ids;

    ShaderId GetMacroBigMask(const std::string& macro);
};

/**
 *	1, manage shaders with id
 *	2, manage shader cache
 */
class RENDER_DLL ShaderMgr
{
    SINGLETON_DECLARE(ShaderMgr);
public:
    ShaderMgr();
    ~ShaderMgr();

    /*
     *	load shaders from cache, 
     *	if cache miss, recompile shader and update cache
     */
    void LoadShaders();

    /*
     *	retrieve shader functions
     */
    ShaderId GetShaderTypeId(const char* name)const;
    ShaderId GetShaderMacroMask(const char* typeName, const char* macroName)const;
    ShaderId GetShaderMacroMask(const ShaderId& typeId, const char* macroName)const;    
    const ShaderHandle* GetShader(const ShaderId& id)const;

    /*
     *	apply shaders
     */
    void ApplyShader(const ShaderHandle* shaderHandle)const;
    void ApplyShader(const ShaderId& shaderId)const;
    

    static bool DetermineShaderAnimation(u32 _BoneNum);
    //utils
protected:

    /*
     *	compile shader from preprocess shader source
     */
    bool CompileShader(ShaderHandle& shaderHandle, bool recordCompiledResult = false);
    /*
     *	create vs/ps from compiled shader src
     */
    bool CreateShader(ShaderHandle& shaderHandle);
    /*
     *	preprocess shader source with macro definitions
     */
    bool PreprocessShader(const wchar_t* path, const D3DXMACRO* defines, LPD3DXINCLUDE includes, ShaderHandle& shaderHandle);

    /*
     *	utils for parse shader descriptions
     */
    void ParseShaderDesc(const BMStr& descPath, ShaderDesc& shaderDesc);
    void ParseShaderNation(TiXmlElement* shaderNation, ShaderDesc& shaderDesc);
    void ParseShaderProvince(TiXmlElement* shaderProvince, ShaderDesc& shaderDesc, std::vector<ShaderId>& ids);    
    
    /*
     *	update shader cache
     */
    void LoadShaderCache();
    void UpdateShaderCache();
    //attr
protected:
    typedef stdext::hash_map<ShaderId, ShaderHandle*> ShaderMap;
    typedef ShaderMap::const_iterator ShaderMapIt;
    typedef stdext::hash_map<ShaderId, TArray<u8>> ShaderCacheContent;
    TArray<ShaderDesc>  mShaderDescs;
    ShaderMap           mShaderMap;    
    ShaderCacheContent  mShaderCache;
};