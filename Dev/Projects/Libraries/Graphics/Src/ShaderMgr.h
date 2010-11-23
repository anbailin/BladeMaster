#pragma once

#include "ShaderId.h"
#include "Shader.h"

struct ShaderDesc
{
    std::string                 name;
    std::vector<std::string>    definitions;
    std::vector<ShaderId>       id;

    ShaderId GetMacroBigMask(const std::string& macro);
};

class ShaderMgr
{
    SINGLETON_DECLARE(ShaderMgr);
public:
    ShaderMgr();
    ~ShaderMgr();

    void LoadShaders();
    ShaderId GetShaderTypeId(const char* name)const;
    ShaderId GetShaderMacroId(const char* typeName, const char* macroName)const;
    
    const ShaderHandle* GetShader(const ShaderId& id)const;

    //utils
protected:
    void ParseShaderDesc(const std::wstring& shaderPath, const std::wstring& descPath, ShaderDesc& shaderDesc);
    void ParseShaderNation(TiXmlElement* shaderNation, ShaderDesc& shaderDesc);
    void ParseShaderProvince(TiXmlElement* shaderProvince, ShaderDesc& shaderDesc, std::vector<ShaderId>& ids);

    //attr
protected:
    TArray<ShaderDesc>         mShaderDescs;
    stdext::hash_map<ShaderId, ShaderHandle*> mShaderMap;
};