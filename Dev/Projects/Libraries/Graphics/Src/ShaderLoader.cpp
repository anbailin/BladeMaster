#include "GraphicsPrivate.h"

//data
BM_SINGLETON_DEFINE(ShaderLoader);
const char* ShaderLoader::ms_VSProfile3 = "vs_3_0";
const char* ShaderLoader::ms_PSProfile3 = "ps_3_0";

//funcs impl

namespace
{
    std::wstring ShaderFullPath;
    const wchar_t* kShaderPath = L"..\\Data\\Shader\\";

    const char* kVSEntry = "MainVS";
    const char* kPSEntry = "MainPS";

    void GetFullShaderPath(const wchar_t* str)
    {       
        //QDir dir("AppData:Shader");
        //ShaderFullPath.assign(dir.absolutePath().toStdWString() + L"\\");
        //ShaderFullPath.assign(kShaderPath);
        ShaderFullPath = L"..\\Engine\\Shader\\";
        ShaderFullPath += str;
    }

    const wchar_t* kShaderFiles[] = 
    {
        L"ModelSkinning.hlsl", //ESF_ModelSkin
        L"ModelStatic.hlsl",   //ESF_ModelStatic
        L"Bone.hlsl",          //ESF_Bone
        L"PostFX.hlsl",        //ESF_PostFX
        L"Terrain.hlsl"        //ESF_Terrain
    };

    const char* kShaderDefines[] = 
    {
        "BLOOM_FILTER", //ESD_PostFx_Bloom_Filter
        "BLOOM_BLURV",  //ESD_PostFx_Bloom_BlurV
        "BLOOM_BLURH",  //ESD_PostFx_Bloom_BlurH
        "BLOOM_MERGE",  //ESD_PostFx_Bloom_Merge
        "COPY_VS",      //ESD_PostFx_Copy_VS
        "COPY_PS"       //ESD_PostFx_Copy_HS
    };    

    D3DXMACRO kShaderMacros[ESD_Num];
}

bool ShaderLoader::LoadPixelShader(
                     //input
                     const wchar_t* path, 
                     const D3DXMACRO* defines, 
                     LPD3DXINCLUDE includes, 
                     const char* entry,
                     DWORD flags,
                     //output
                     PixelShaderPtr& pixeShader
                     )
{
    entry = entry==NULL?kPSEntry:entry;

    GetFullShaderPath(path);

    //if fail, buffer is still NULL, so not necessary to release buffer
    //if succeed, we need to release before return
    ID3DXBuffer* buffer = NULL;
    //if fail, we need to release before return
    //if succeed, errorMsg is still NULL, so not necessary to release buffer
    ID3DXBuffer* errorMsg = NULL;

    if(SUCCEEDED(D3DXCompileShaderFromFile(ShaderFullPath.c_str(), defines, includes, entry, ms_PSProfile3, 0, &buffer, &errorMsg, NULL))==false)
    {
        //logout errors
        LogToDebug((const char*)errorMsg->GetBufferPointer());
        errorMsg->Release(); 
        assert(0);
        return false;
    }	    
    
    const bool result = SUCCEEDED( DEVICEPTR->CreatePixelShader(static_cast<DWORD*>(buffer->GetBufferPointer()), &pixeShader) );
    buffer->Release();
    return result;
}

bool ShaderLoader::LoadVertexShader(
                      //input
                      const wchar_t* path, 
                      const D3DXMACRO* defines, 
                      LPD3DXINCLUDE includes,   
                      const char* entry,
                      DWORD flags,
                      //output
                      VertexShaderPtr& vertexShader
                      )
{
    entry = entry==NULL?kVSEntry:entry;
    GetFullShaderPath(path);

    //if fail, buffer is still NULL, so not necessary to release buffer
    //if succeed, we need to release before return
    ID3DXBuffer* buffer = NULL;
    //if fail, we need to release before return
    //if succeed, errorMsg is still NULL, so not necessary to release buffer
    ID3DXBuffer* errorMsg = NULL;

    if(SUCCEEDED(D3DXCompileShaderFromFile(ShaderFullPath.c_str(), defines, includes, entry, ms_VSProfile3, 0, &buffer, &errorMsg, NULL))==false)
    {
        //logout errors
        LogToDebug((const char*)errorMsg->GetBufferPointer());
        errorMsg->Release(); 
        assert(0);
        return false;
    }	    

    const bool result = SUCCEEDED( DEVICEPTR->CreateVertexShader(static_cast<DWORD*>(buffer->GetBufferPointer()), &vertexShader) );
    buffer->Release();
    return result;
}

void ShaderLoader::CreateShaderCache()
{
    //init skinning shader
    VertexShaderPtr skin_vs_ptr;
    PixelShaderPtr skin_ps_ptr;

    LoadVertexShader(kShaderFiles[ESF_ModelSkin],NULL, NULL, NULL, 0, skin_vs_ptr);
    LoadPixelShader(kShaderFiles[ESF_ModelSkin],NULL,NULL, NULL, 0, skin_ps_ptr);

    mVSMap[skin_vs_id] = skin_vs_ptr;
    mPSMap[skin_ps_id] = skin_ps_ptr;

    //init static shader
    VertexShaderPtr static_vs_ptr;
    PixelShaderPtr static_ps_ptr;

    LoadVertexShader(kShaderFiles[ESF_ModelStatic], NULL, NULL, NULL, 0,static_vs_ptr);
    LoadPixelShader(kShaderFiles[ESF_ModelStatic],NULL,NULL,NULL, 0,static_ps_ptr);
    mVSMap[static_vs_id] = static_vs_ptr;
    mPSMap[static_ps_id] = static_ps_ptr;

    //init bone shader
    VertexShaderPtr bone_vs_ptr;
    PixelShaderPtr bone_ps_ptr;

    LoadVertexShader(kShaderFiles[ESF_Bone], NULL, NULL, NULL, 0, bone_vs_ptr);
    LoadPixelShader(kShaderFiles[ESF_Bone], NULL, NULL, NULL, 0, bone_ps_ptr);

    mVSMap[bone_vs_id] = bone_vs_ptr;
    mPSMap[bone_ps_id] = bone_ps_ptr;

    //terrain shader
    VertexShaderPtr terrain_vs_ptr;
    PixelShaderPtr terrain_ps_ptr;

    LoadVertexShader(kShaderFiles[ESF_Terrain], NULL, NULL, NULL, 0, terrain_vs_ptr);
    LoadPixelShader(kShaderFiles[ESF_Terrain], NULL, NULL, NULL, 0, terrain_ps_ptr);

    mVSMap[terrain_vs_id] = terrain_vs_ptr;
    mPSMap[terrain_ps_id] = terrain_ps_ptr;

    //init postfx shader
    D3DXMACRO postfx_shader_macro[2];
    postfx_shader_macro[1].Name = NULL;
    postfx_shader_macro[1].Definition = NULL;

    //postfx_bloom_filter_vs_id
    VertexShaderPtr postfx_bloom_filter_vs;
    postfx_shader_macro[0] = kShaderMacros[ESD_PostFx_Bloom_Filter];
    LoadVertexShader(kShaderFiles[ESF_PostFX], &postfx_shader_macro[0], NULL, NULL, 0, postfx_bloom_filter_vs);
    mVSMap[postfx_bloom_filter_vs_id] = postfx_bloom_filter_vs;

    //postfx_bloom_filter_ps_id
    PixelShaderPtr postfx_bloom_filter_ps;
    postfx_shader_macro[0] = kShaderMacros[ESD_PostFx_Bloom_Filter];
    LoadPixelShader(kShaderFiles[ESF_PostFX], &postfx_shader_macro[0], NULL, NULL, 0, postfx_bloom_filter_ps);
    mPSMap[postfx_bloom_filter_ps_id] = postfx_bloom_filter_ps;

    //postfx_bloom_blurv_ps_id
    PixelShaderPtr postfx_bloom_blurv_ps;
    postfx_shader_macro[0] = kShaderMacros[ESD_PostFx_Bloom_BlurV];
    LoadPixelShader(kShaderFiles[ESF_PostFX], &postfx_shader_macro[0], NULL, NULL, 0, postfx_bloom_blurv_ps);
    mPSMap[postfx_bloom_blurv_ps_id] = postfx_bloom_blurv_ps;

    //postfx_bloom_blurh_ps_id
    PixelShaderPtr postfx_bloom_blurh_ps;
    postfx_shader_macro[0] = kShaderMacros[ESD_PostFx_Bloom_BlurH];
    LoadPixelShader(kShaderFiles[ESF_PostFX], &postfx_shader_macro[0], NULL, NULL, 0, postfx_bloom_blurh_ps);
    mPSMap[postfx_bloom_blurh_ps_id] = postfx_bloom_blurh_ps;

    //postfx_bloom_merge_ps_id
    PixelShaderPtr postfx_bloom_merge_ps;
    postfx_shader_macro[0] = kShaderMacros[ESD_PostFx_Bloom_Merge];
    LoadPixelShader(kShaderFiles[ESF_PostFX], &postfx_shader_macro[0], NULL, NULL, 0, postfx_bloom_merge_ps);
    mPSMap[postfx_bloom_merge_ps_id] = postfx_bloom_merge_ps;

    //postfx_copy_ps_id
    PixelShaderPtr postfx_bloom_copy_ps;
    postfx_shader_macro[0] = kShaderMacros[ESD_PostFx_Copy_PS];
    LoadPixelShader(kShaderFiles[ESF_PostFX], &postfx_shader_macro[0], NULL, NULL, 0, postfx_bloom_copy_ps);
    mPSMap[postfx_copy_ps_id] = postfx_bloom_copy_ps;

    //postfx_copy_vs_id
    VertexShaderPtr postfx_copy_vs;
    postfx_shader_macro[0] = kShaderMacros[ESD_PostFx_Copy_VS];
    LoadVertexShader(kShaderFiles[ESF_PostFX], &postfx_shader_macro[0], NULL, NULL, 0, postfx_copy_vs);
    mVSMap[postfx_copy_vs_id] = postfx_copy_vs;
}

void ShaderLoader::Init()
{
    /**
    *   init shader id
    */
    //init skinning shader
    skin_vs_id = ESF_ModelSkin;
    skin_ps_id = ESF_ModelSkin;

    //init static shader
    static_vs_id = ESF_ModelStatic;
    static_ps_id = ESF_ModelStatic;

    //init bone shader
    bone_vs_id = ESF_Bone;
    bone_ps_id = ESF_Bone;

    //init terrain shader
    terrain_vs_id = ESF_Terrain;
    terrain_ps_id = ESF_Terrain;

    //init postfx shader
    uint64 postfx_file_id = ESF_PostFX;
    postfx_file_id = postfx_file_id<<32;
    postfx_bloom_filter_vs_id = postfx_file_id |  0x1<<ESD_PostFx_Bloom_Filter;
    postfx_bloom_filter_ps_id = postfx_file_id |  0x1<<ESD_PostFx_Bloom_Filter;
    postfx_copy_vs_id = postfx_file_id | 0x1<<ESD_PostFx_Copy_VS;
    postfx_bloom_blurv_ps_id = postfx_file_id | 0x1<<ESD_PostFx_Bloom_BlurV;
    postfx_bloom_blurh_ps_id = postfx_file_id | 0x1<<ESD_PostFx_Bloom_BlurH;
    postfx_bloom_merge_ps_id = postfx_file_id | 0x1<<ESD_PostFx_Bloom_Merge;
    postfx_copy_ps_id = postfx_file_id | 0x1<<ESD_PostFx_Copy_PS;

    /*
    *   init macros
    */
    for(uint32 i=0; i<ESD_Num; i++)
    {
        kShaderMacros[i].Name = kShaderDefines[i];
    }
}

void ShaderLoader::ApplyShader(uint64 vs_id, uint64 ps_id)
{
    std::map<uint64,VertexShaderPtr>::iterator vs_it = mVSMap.find(vs_id);
    assert(vs_it!=mVSMap.end());

    std::map<uint64,PixelShaderPtr>::iterator ps_it = mPSMap.find(ps_id);    
    assert(ps_it!=mPSMap.end());

    DEVICEPTR->SetPixelShader(ps_it->second);
    DEVICEPTR->SetVertexShader(vs_it->second);
}

void ShaderLoader::RefreshShaderCaceh()
{
    DestroyShaderCache();
    CreateShaderCache();    
}

void ShaderLoader::DestroyShaderCache()
{
    std::map<uint64,VertexShaderPtr>::iterator vs_begin_it = mVSMap.begin();
    std::map<uint64,VertexShaderPtr>::iterator vs_end_it = mVSMap.end();

    for(std::map<uint64,VertexShaderPtr>::iterator it = vs_begin_it; it!=vs_end_it; it++)
    {
        it->second = NULL;
    }

    std::map<uint64,PixelShaderPtr>::iterator ps_begin_it = mPSMap.begin();
    std::map<uint64,PixelShaderPtr>::iterator ps_end_it = mPSMap.end();

    for(std::map<uint64,PixelShaderPtr>::iterator it = ps_begin_it; it!=ps_end_it; it++)
    {
        it->second = NULL;
    }
}