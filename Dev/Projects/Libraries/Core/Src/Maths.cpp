#include "CorePrivate.h"

#include "Maths.h"
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "Quaternion.h"

namespace BM
{
    //////////////////////////////////////////////////////////////////////////
    // Vector Constants
    const Vector2 Vector2::Zero(0.0f, 0.0f);
    const Vector2 Vector2::One(1.0f, 1.0f);
    const Vector2 Vector2::BaseX(1.0f, 0.0f);
    const Vector2 Vector2::BaseY(0.0f, 1.0f);

    const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
    const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
    const Vector3 Vector3::BaseX(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::BaseY(0.0f, 1.0f, 0.0f);
    const Vector3 Vector3::BaseZ(0.0f, 0.0f, 1.0f);

    const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);
    const Vector4 Vector4::BaseX(1.0f, 0.0f, 0.0f, 0.0f);
    const Vector4 Vector4::BaseY(0.0f, 1.0f, 0.0f, 0.0f);
    const Vector4 Vector4::BaseZ(0.0f, 0.0f, 1.0f, 0.0f);
    const Vector4 Vector4::BaseW(0.0f, 0.0f, 0.0f, 1.0f);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Matrix Constants
    const Matrix44 Matrix44::Zero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    const Matrix44 Matrix44::Identity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Quaternion Constants
    const Quaternion Quaternion::Zero(0.0f, 0.0f, 0.0f, 0.0f);
    const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Color Constants
    const Color Color::Zero(0.0f, 0.0f, 0.0f, 0.0f);
    const Color Color::One(1.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::Black(0.0f, 0.0f, 0.0f);
    const Color Color::White(1.0f, 1.0f, 1.0f);
    const Color Color::Red(1.0f, 0.0f, 0.0f);
    const Color Color::Green(0.0f, 1.0f, 0.0f);
    const Color Color::Blue(0.0f, 0.0f, 1.0f);
    //////////////////////////////////////////////////////////////////////////
}
