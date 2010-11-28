#pragma once

/*
 *	upper 32 bit for shader type information, can't do bit operation
 *	lower 32 bit for shader macro, can do bit operation for macro combination
 */
typedef u64 ShaderId;
#define InvalidShaderTypeId 0xffffffff00000000
#define InvalidShaderMacroId 0x00000000ffffffff
#define InvalidShaderId 0xffffffffffffffff

//class 
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