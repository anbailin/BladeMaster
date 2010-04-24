#include "GamePrivate.h"
#include "GameApplication.h"

namespace BM
{
    GameApplication::GameApplication(QString name, QWidget* pRenderWidget, int argc, char* argv[])
        : Application(name, argc, argv)
        , m_TickTimer(this)
    {
        // this widget will be used as render target
        //m_pRenderWidget = pRenderWidget;
        //BM_Assert(m_pRenderWidget != NULL);

        connect(&m_TickTimer, SIGNAL(timeout()), this, SLOT(Tick()));
    }

    bool GameApplication::Init(QWidget* pRenderWidget)
    {
		m_pRenderWidget = pRenderWidget;
		BM_Assert(m_pRenderWidget != NULL);

        if (!Application::Init())
        {
            return false;
        }

        if (!InitApp())
        {
            return false;
        }

        if (!InitEngine())
        {
            return false;
        }

        m_TickTimer.start();
        return true;
    }

    bool GameApplication::InitApp()
    {
        return true;
    }

    bool GameApplication::InitEngine()
    {
        //m_pGameEngine = new GameEngine();
        //m_pGameEngine->Init(m_pRenderWidget);
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
