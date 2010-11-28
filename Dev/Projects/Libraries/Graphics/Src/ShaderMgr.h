#pragma once
#include "Shader.h"

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
class ShaderMgr
{
    SINGLETON_DECLARE(ShaderMgr);
public:
    ShaderMgr();
    ~ShaderMgr();

    void LoadShaders();
    ShaderId GetShaderTypeId(const char* name)const;
    ShaderId GetShaderMacroMask(const char* typeName, const char* macroName)const;
    ShaderId GetShaderMacroMask(const ShaderId& typeId, const char* macroName)const;
    
    const ShaderHandle* GetShader(const ShaderId& id)const;
    void ApplyShader(const ShaderHandle* shaderHandle)const;
    void ApplyShader(const ShaderId& shaderId)const;

    bool CompileShader(
        const wchar_t* path, 
        const D3DXMACRO* defines, 
        LPD3DXINCLUDE includes,         
        DWORD flags,
        PixelShaderPtr& pixeShader,
        VertexShaderPtr& vertexShader,
        TArray<u8>& vsCode,
        TArray<u8>& psCode
        );

    bool CompileShader(ShaderHandle& shaderHandle, bool recordCompiledResult = false);
    bool CreateShader(ShaderHandle& shaderHandle);
    bool PreprocessShader(const wchar_t* path, const D3DXMACRO* defines, LPD3DXINCLUDE includes, ShaderHandle& shaderHandle);

    //utils
protected:
    void ParseShaderDesc(const BMStr& descPath, ShaderDesc& shaderDesc);
    void ParseShaderNation(TiXmlElement* shaderNation, ShaderDesc& shaderDesc);
    void ParseShaderProvince(TiXmlElement* shaderProvince, ShaderDesc& shaderDesc, std::vector<ShaderId>& ids);    
    
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