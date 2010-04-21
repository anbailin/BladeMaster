#include "GraphicsPrivate.h"
#include "Renderer.h"

namespace BM
{
    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Init(QWidget* pRenderWidget)
    {
    }

    void Renderer::Exit()
    {
        SafeDelete(m_pRenderWindow);
    }

    void Renderer::Tick()
    {
    }
}
