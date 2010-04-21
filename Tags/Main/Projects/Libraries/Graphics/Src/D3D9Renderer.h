#pragma once

#include "GraphicsPublic.h"
#include "D3D9.h"
#include "Renderer.h"

namespace BM
{
    class GRAPHICS_API D3D9Renderer : public Renderer
    {
        Q_OBJECT

    public:
        D3D9Renderer();
        virtual ~D3D9Renderer();

    public:
        virtual void Init(QWidget* pRenderWidget);
        virtual void Exit();
        virtual void Tick();

    private:
        void CreateD3DDevice();

    private:
        IDirect3D9*             m_pD3D;
        IDirect3DDevice9*       m_pD3DDevice;
        D3DPRESENT_PARAMETERS   m_PresentParameters;
    };
}
