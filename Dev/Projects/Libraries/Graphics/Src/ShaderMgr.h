#pragma once

#include "ShaderId.h"
#include "Shader.h"

class ShaderMgr
{
    SINGLETON_DECLARE(ShaderMgr);
public:
    ShaderMgr();
    ~ShaderMgr();

    void LoadShaders();

public:
    struct ShaderDesc
    {
        std::string                 name;
        std::vector<std::string>    definitions;
    };
    std::vector<ShaderDesc>         mShaderDescs;
    stdext::hash_map<ShaderId, ShaderHandle*> mShaderMap;
};