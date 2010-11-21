#pragma once

class ShaderHandle
{
public:
    VertexShaderPtr  mVertexShader;
    PixelShaderPtr   mPixelShader;
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