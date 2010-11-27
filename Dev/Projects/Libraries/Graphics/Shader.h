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
class ShaderHandle
{
public:
    VertexShaderPtr  mVertexShader;
    PixelShaderPtr   mPixelShader;
    TArray<u8>       mVSCompiledShader;
    TArray<u8>       mPSCompiledShader;
};

class VSHandle
{
public:
    VSHandle();
    void Init();
    IDirect3DVertexShader9* GetVertexShader() { return mVertexShader; }
protected:
    ComPtr<IDirect3DVertexShader9>  mVertexShader;
};

class PSHandle
{
protected:
    ComPtr<IDirect3DPixelShader9> mPixelShader;
};