#pragma once

enum EShaderFile
{
    ESF_ModelSkin,
    ESF_ModelStatic,
    ESF_Bone,
    ESF_PostFX,
    ESF_Terrain,
    ESF_ShaderFileNum
};

enum EShaderDefine
{
//postfx
    ESD_PostFx_Bloom_Filter ,
    ESD_PostFx_Bloom_BlurV ,
    ESD_PostFx_Bloom_BlurH ,
    ESD_PostFx_Bloom_Merge ,
    ESD_PostFx_Copy_VS ,
    ESD_PostFx_Copy_PS ,
    ESD_Num
};

class ShaderLoader
{
    SINGLETON_DECLARE(ShaderLoader);

    //funcs
public:
    bool LoadPixelShader(
        //input
        const wchar_t* path, 
        const D3DXMACRO* defines, 
        LPD3DXINCLUDE includes,  
        const char* entry,
        DWORD flags,
        //output
        PixelShaderPtr& pixeShader
        );
    bool LoadVertexShader(
        //input
        const wchar_t* path, 
        const D3DXMACRO* defines, 
        LPD3DXINCLUDE includes,      
        const char* entry,
        DWORD flags,
        //output
        VertexShaderPtr& vertexShader
        );

    void Init();

    void CreateShaderCache();
    void DestroyShaderCache();
    void RefreshShaderCaceh();

    void ApplyShader(uint64 vs_id, uint64 ps_id);

    //attributes
public:
    static const char* ms_VSProfile3;
    static const char* ms_PSProfile3;
    uint64 skin_vs_id;
    uint64 skin_ps_id;
    uint64 static_vs_id;
    uint64 static_ps_id;
    uint64 bone_vs_id;
    uint64 bone_ps_id;
    uint64 terrain_vs_id;
    uint64 terrain_ps_id;
    uint64 postfx_bloom_filter_vs_id;
    uint64 postfx_bloom_filter_ps_id;
    uint64 postfx_copy_vs_id;
    uint64 postfx_bloom_blurv_ps_id;
    uint64 postfx_bloom_blurh_ps_id;
    uint64 postfx_bloom_merge_ps_id;
    uint64 postfx_copy_ps_id;

protected:
    std::map<uint64,PixelShaderPtr>     mPSMap;
    std::map<uint64,VertexShaderPtr>    mVSMap;
};