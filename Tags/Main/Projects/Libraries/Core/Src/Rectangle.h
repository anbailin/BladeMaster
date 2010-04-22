#pragma once

#include "CorePublic.h"

namespace BM
{
    template<typename T>
    class CORE_API Rectangle
    {
    public:
        T Left;
        T Top;
        T Width;
        T Height;

    public:
        Rectangle()
        {
            Left   = T(0);
            Top    = T(0);
            Width  = T(0);
            Height = T(0);
        }

        Rectangle(T left, T top, T width, T height)
        {
            Left   = left;
            Top    = top;
            Width  = width;
            Height = height;
        }

        Rectangle(const Rectangle& other)
        {
            Left   = other.Left;
            Top    = other.Top;
            Width  = other.Width;
            Height = other.Height;
        }

    public:
        T Right() const
        {
            return Left + Width;
        }

        T Bottom() const
        {
            return Top + Height;
        }

        void Set(T left, T top, T width, T height)
        {
            Left   = left;
            Top    = top;
            Width  = width;
            Height = height;
        }

        void Empty()
        {
            Left   = T(0);
            Top    = T(0);
            Width  = T(0);
            Height = T(0);
        }

        bool IsEmpty() const
        {
            return (Left == T(0) && Top == T(0) && Width == T(0) && Height == T(0));
        }

        Rectangle& operator = (const Rectangle& other)
        {
            Left   = other.Left;
            Top    = other.Top;
            Width  = other.Width;
            Height = other.Height;
            return *this;
        }

        bool operator == (const Rectangle& other) const
        {
            return (Left == other.Left && Top == other.Top && Width == other.Width && Height == other.Height);
        }

        bool operator != (const Rectangle& other) const
        {
            return (Left != other.Left || Top != other.Top || Width != other.Width || Height != other.Height);
        }
    };
}
