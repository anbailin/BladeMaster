#pragma once

#include "GamePublic.h"

namespace BM
{
    class GAME_API GameApplication : public Application
    {
        Q_OBJECT

    public:
        GameApplication(QString name, int argc, char* argv[]);
        ~GameApplication();

    protected:
        virtual bool InitApp();
        virtual bool InitEngine();

        void SetRenderWidget(QWidget* pRenderWidget) { m_pRenderWidget = pRenderWidget; }

    protected slots:
        virtual void Exit();
        virtual void Tick();

    private:
        virtual bool Init();

    protected:
        QTimer                  m_TickTimer;
        QPointer<QWidget>       m_pRenderWidget;
        QPointer<Renderer>      m_pRenderer;
        QPointer<GameEngine>    m_pEngine;
        Timer                   m_Timer;
    };
}
