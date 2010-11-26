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

    public:
        Timer& GetTimer() { return m_Timer; }

    protected:
        virtual bool InitApp();
        virtual bool InitEngine();
        virtual void Tick(f32 fDeltaTime);

        void SetRenderWidget(QWidget* pRenderWidget) { m_pRenderWidget = pRenderWidget; }

    protected slots:
        virtual void Exit();

    private slots:
        virtual bool Init();
        virtual void OnTick();

    protected:
        QTimer                  m_TickTimer;
        QPointer<QWidget>       m_pRenderWidget;
        QPointer<Renderer>      m_pRenderer;
        QPointer<GameEngine>    m_pEngine;
        Timer                   m_Timer;
    };
}
