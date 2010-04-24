#pragma once

#include "GamePublic.h"

namespace BM
{
    class GAME_API GameApplication : public Application
    {
        Q_OBJECT

    public:
        GameApplication(QString name, QWidget* pRenderWidget, int argc, char* argv[]);

    protected:
        virtual bool InitApp();
        virtual bool InitEngine();

    protected slots:
        virtual void Exit();
        virtual void Tick();

    public:
        virtual bool Init(QWidget* pRenderWidget);

    protected:
        QTimer                      m_TickTimer;
        QPointer<GameEngine>        m_pGameEngine;
        QPointer<QWidget>           m_pRenderWidget;
    };
}
