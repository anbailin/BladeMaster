#include "EnginePrivate.h"
#include "GameEngine.h"

namespace BM
{
    GameEngine::GameEngine()
    {
    }
    
    GameEngine::~GameEngine()
    {

    }

    void GameEngine::Init(QWidget* pRenderWidget)
    {
        m_pRenderer = new D3D9Renderer();
        m_pRenderer->Init(pRenderWidget);
    }

    void GameEngine::Exit()
    {
        SafeDelete(m_pRenderer);
    }

    void GameEngine::Tick()
    {
        m_pRenderer->Tick();
    }
}
