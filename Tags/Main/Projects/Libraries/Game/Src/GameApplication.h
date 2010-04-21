#pragma once

#include "GamePublic.h"

namespace BM
{
    class GAME_API GameApplication : public Application
    {
        Q_OBJECT

    public:
        GameApplication(int argc, char* argv[]);

    protected:
        virtual bool Init();

    protected slots:
        virtual void Exit();
        virtual void Tick();

    protected:
        QTimer                      m_TickTimer;
        QPointer<GameEngine>        m_pGameEngine;
        QPointer<QWidget>           m_pRenderWidget;
    };
}
