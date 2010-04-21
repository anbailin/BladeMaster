#pragma once

#include "GraphicsPublic.h"
#include "RenderWindow.h"

namespace BM
{
    class D3D9RenderWindow : public RenderWindow
    {
        Q_OBJECT

    public:
        D3D9RenderWindow(QWidget* pWidget);
        virtual ~D3D9RenderWindow();
    };
}
