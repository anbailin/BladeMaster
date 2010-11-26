#pragma once

#include "ShaderId.h"
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
        VertexShaderPtr& vertexShader
        );

    //utils
protected:
    void ParseShaderDesc(const BMStr& descPath, ShaderDesc& shaderDesc);
    void ParseShaderNation(TiXmlElement* shaderNation, ShaderDesc& shaderDesc);
    void ParseShaderProvince(TiXmlElement* shaderProvince, ShaderDesc& shaderDesc, std::vector<ShaderId>& ids);    

    //attr
protected:
    TArray<ShaderDesc>         mShaderDescs;
    stdext::hash_map<ShaderId, ShaderHandle*> mShaderMap;
};