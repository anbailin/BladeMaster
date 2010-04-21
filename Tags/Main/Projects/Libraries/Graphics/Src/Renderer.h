#pragma once

#include "GraphicsPublic.h"
#include "RenderWindow.h"

namespace BM
{
    class GRAPHICS_API Renderer : public QObject
    {
        Q_OBJECT

    public:
        Renderer();
        virtual ~Renderer();

    public:
        virtual void Init(QWidget* pRenderWidget);
        virtual void Exit();
        virtual void Tick();

        RenderWindow& Window() const { return *m_pRenderWindow; }

    protected:
        QPointer<RenderWindow>  m_pRenderWindow;
    };
}
