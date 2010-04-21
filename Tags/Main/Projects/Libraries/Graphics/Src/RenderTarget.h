#pragma once

#include "GraphicsPublic.h"

namespace BM
{
    class GRAPHICS_API RenderTarget : public QObject
    {
        Q_OBJECT

    public:
        RenderTarget();
        virtual ~RenderTarget();
    };
}
