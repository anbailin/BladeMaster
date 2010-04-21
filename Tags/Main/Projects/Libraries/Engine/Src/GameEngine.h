#pragma once

#include "EnginePublic.h"

namespace BM
{
    class ENGINE_API GameEngine : public QObject
    {
        Q_OBJECT

    public:
        GameEngine();
        virtual ~GameEngine();

    public:
        virtual void Init(QWidget* pRenderWidget);
        virtual void Exit();
        virtual void Tick();

    private:
        QPointer<Renderer> m_pRenderer;
    };
}
