#include "GraphicsPrivate.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(QWidget* pRenderWidget)
{
    m_pRenderWidget = pRenderWidget;
    BM_Assert(m_pRenderWidget != NULL);
}

void Renderer::Exit()
{
}

void Renderer::Tick(f32 fDeltaTime)
{
}
