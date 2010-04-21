#include "GraphicsPrivate.h"
#include "RenderWindow.h"

namespace BM
{
    RenderWindow::RenderWindow(QWidget* pWidget)
    {
        m_pWidget = pWidget;
    }

    RenderWindow::~RenderWindow()
    {
    }
}
