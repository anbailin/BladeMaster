#pragma once

#include "GraphicsPublic.h"
#include "RenderTarget.h"

namespace BM
{
    class GRAPHICS_API RenderWindow : public RenderTarget
    {
        Q_OBJECT

    public:
        RenderWindow(QWidget* pWidget);
        ~RenderWindow();

    public:
        HWND Handle() const { return m_pWidget->winId(); }
        int Height() const { return m_pWidget->height(); }
        int Width() const { return m_pWidget->width(); }

    protected:
        QPointer<QWidget> m_pWidget;
    };
}
