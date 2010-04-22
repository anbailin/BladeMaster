#pragma once

#include "CorePublic.h"

namespace BM
{
    class Radian;

	class Degree
	{
	public:
        inline Degree()                                         { m_Value = 0.0f; }
        inline Degree(Float32 d)                                { m_Value = d; }
        inline Degree(const Radian& r);

		inline bool operator == (const Degree& d) const         { return m_Value == d.m_Value; }
		inline bool operator != (const Degree& d) const         { return m_Value != d.m_Value; }
		inline bool operator <  (const Degree& d) const         { return m_Value <  d.m_Value; }
		inline bool operator <= (const Degree& d) const         { return m_Value <= d.m_Value; }
		inline bool operator >  (const Degree& d) const         { return m_Value >  d.m_Value; }
		inline bool operator >= (const Degree& d) const         { return m_Value >= d.m_Value; }

		inline Degree& operator = (Float32 d)                   { m_Value = d; return *this; }
		inline Degree& operator = (const Degree& d)             { m_Value = d.m_Value; return *this; }
		inline Degree& operator = (const Radian& r);

		inline Degree& operator += (const Degree& d)            { m_Value += d.m_Value; return *this; }
		inline Degree& operator -= (const Degree& d)            { m_Value -= d.m_Value; return *this; }

		inline Degree& operator += (const Radian& r);
		inline Degree& operator -= (const Radian& r);

		inline Degree& operator *= (Float32 f)                  { m_Value *= f; return *this; }
		inline Degree& operator /= (Float32 f)                  { m_Value /= f; return *this; }

		inline Degree operator + () const                       { return *this; }
		inline Degree operator - () const                       { return Degree(-m_Value); }

		inline Degree operator + (const Degree& d) const        { return Degree(m_Value + d.m_Value); }
		inline Degree operator - (const Degree& d) const        { return Degree(m_Value - d.m_Value); }

		inline Degree operator + (const Radian& r) const;
		inline Degree operator - (const Radian& r) const;

		inline Degree operator * (Float32 f) const              { return Degree(m_Value * f); }
		inline Degree operator / (Float32 f) const              { return Degree(m_Value / f); }

		inline Float32 GetDegree() const                        { return m_Value; }
        inline Float32 GetRadian() const                        { return DegreeToRadian(m_Value); }

    private:
        Float32 m_Value;
	};

	class Radian
	{
	public:
        inline Radian()                                         { m_Value = 0.0f; }
        inline Radian(Float32 r)                                { m_Value = r; }
        inline Radian(const Degree& d);

		inline bool operator <  (const Radian& r) const         { return m_Value <  r.m_Value; }
		inline bool operator <= (const Radian& r) const         { return m_Value <= r.m_Value; }
		inline bool operator == (const Radian& r) const         { return m_Value == r.m_Value; }
		inline bool operator != (const Radian& r) const         { return m_Value != r.m_Value; }
		inline bool operator >= (const Radian& r) const         { return m_Value >= r.m_Value; }
		inline bool operator >  (const Radian& r) const         { return m_Value >  r.m_Value; }

		inline Radian& operator = (Float32 r)                   { m_Value = r; return *this; }
		inline Radian& operator = (const Radian& r)             { m_Value = r.m_Value; return *this; }
		inline Radian& operator = (const Degree& d);

		inline Radian& operator += (const Radian& r)            { m_Value += r.m_Value; return *this; }
		inline Radian& operator -= (const Radian& r)            { m_Value -= r.m_Value; return *this; }

		inline Radian& operator += (const Degree& d);
		inline Radian& operator -= (const Degree& d);

        inline Radian& operator *= (Float32 f)                  { m_Value *= f; return *this; }
        inline Radian& operator /= (Float32 f)                  { m_Value /= f; return *this; }

        inline Radian operator + () const                       { return *this; }
		inline Radian operator - () const                       { return Radian(-m_Value); }

		inline Radian operator + (const Radian& r) const        { return Radian(m_Value + r.m_Value); }
		inline Radian operator - (const Radian& r) const        { return Radian(m_Value - r.m_Value); }

		inline Radian operator + (const Degree& d) const;
		inline Radian operator - (const Degree& d) const;

		inline Radian operator * (Float32 f) const              { return Radian(m_Value * f); }
		inline Radian operator / (Float32 f) const              { return Radian(m_Value / f); }

        inline Float32 GetDegree() const                        { return RadianToDegree(m_Value); }
		inline Float32 GetRadian() const                        { return m_Value; }

    private:
        Float32 m_Value;
    };

    inline Degree::Degree(const Radian& r)                      { m_Value = r.GetDegree(); }
    inline Degree& Degree::operator = (const Radian& r)         { m_Value = r.GetDegree(); return *this; }
    inline Degree& Degree::operator += (const Radian& r)        { m_Value += r.GetDegree(); return *this; }
    inline Degree& Degree::operator -= (const Radian& r)        { m_Value -= r.GetDegree(); return *this; }
    inline Degree  Degree::operator + (const Radian& r) const   { return Degree(m_Value + r.GetDegree()); }
    inline Degree  Degree::operator - (const Radian& r) const   { return Degree(m_Value - r.GetDegree()); }

    inline Radian::Radian(const Degree& d)                      { m_Value = d.GetRadian(); }
    inline Radian& Radian::operator = (const Degree& d)         { m_Value = d.GetRadian(); return *this; }
    inline Radian& Radian::operator += (const Degree& d)        { m_Value += d.GetRadian(); return *this; }
    inline Radian& Radian::operator -= (const Degree& d)        { m_Value -= d.GetRadian(); return *this; }
    inline Radian  Radian::operator + (const Degree& d) const   { return Radian(m_Value + d.GetRadian()); }
    inline Radian  Radian::operator - (const Degree& d) const   { return Radian(m_Value - d.GetRadian()); }
}
