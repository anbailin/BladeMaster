#pragma once

//#include "Core.h"

namespace BM
{
    template<typename T>
    class CORE_DLL Point
    {
    public:
        T X;
        T Y;

    public:
        Point()
        {
            X = T(0);
            Y = T(0);
        }

        Point(T x, T y)
        {
            X = x;
            Y = y;
        }

        Point(const Point& other)
        {
            X = other.X;
            Y = other.Y;
        }

    public:
        void Set(T x, T y)
        {
            X = x;
            Y = y;
        }

        void Empty()
        {
            X = T(0);
            Y = T(0);
        }

        bool IsEmpty() const
        {
            return (X == T(0) && Y == T(0));
        }
        
        Point& operator = (const Point& other)
        {
            X = other.X;
            Y = other.Y;
            return *this;
        }

        bool operator == (const Point& other) const
        {
            return (X == other.X && Y == other.Y);
        }

        bool operator != (const Point& other) const
        {
            return (X != other.X || Y != other.Y);
        }
    };
}
