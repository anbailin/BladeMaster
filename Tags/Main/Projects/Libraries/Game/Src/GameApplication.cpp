#include "GamePrivate.h"
#include "GameApplication.h"

namespace BM
{
    GameApplication::GameApplication(int argc, char* argv[])
        : Application(argc, argv)
        , m_TickTimer(this)
    {
        connect(&m_TickTimer, SIGNAL(timeout()), this, SLOT(Tick()));
    }

    bool GameApplication::Init()
    {
        if (!Application::Init())
        {
            return false;
        }

        BM_Assert(m_pRenderWidget != NULL);

        //m_pGameEngine = new GameEngine();
        //m_pGameEngine->Init(m_pRenderWidget);

        m_TickTimer.start();

        return true;
    }

    void GameApplication::Exit()
    {
        SafeDelete(m_pGameEngine);

        Application::Exit();
    }

    void GameApplication::Tick()
    {
        //m_pGameEngine->Tick();
    }
}
