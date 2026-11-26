//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/03/09
//
// File Name : CCameraManager.h
//
// 기본 자료형 정의
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>
#include <type_traits>

#define SAFE_DELETE(a) if(a!=0) delete a

typedef short s16;
typedef int s32;
typedef float f32;
typedef unsigned int u32;

// Integer coordinates use a floating-point result for distances and normalization.
template<typename T>
using vector_length_t = std::conditional_t<std::is_floating_point_v<T>, T, double>;

/// 2차원 벡터의 성분과 기본 산술, 길이, 정규화 연산을 제공한다.
template<typename T>
class vector2d
{
public:
    using length_type = vector_length_t<T>;

    constexpr vector2d() = default;
    constexpr vector2d(T x, T y) : X(x), Y(y) {}

    constexpr vector2d operator+(const vector2d& rhs) const { return {X + rhs.X, Y + rhs.Y}; }
    constexpr vector2d operator-(const vector2d& rhs) const { return {X - rhs.X, Y - rhs.Y}; }
    constexpr vector2d operator*(T scale) const { return {X * scale, Y * scale}; }

    constexpr length_type dot(const vector2d& rhs) const
    {
        return static_cast<length_type>(X) * rhs.X + static_cast<length_type>(Y) * rhs.Y;
    }
    constexpr length_type getLengthSquared() const { return dot(*this); }
    length_type getLength() const { return std::hypot(static_cast<length_type>(X), static_cast<length_type>(Y)); }

    vector2d<length_type> normalize() const
    {
        const auto length = getLength();
        return length > 0 && std::isfinite(length)
            ? vector2d<length_type>{X / length, Y / length}
            : vector2d<length_type>{};
    }

    T X{}, Y{};
};

template<typename T>
constexpr vector2d<T> operator*(T scale, const vector2d<T>& value)
{
    return value * scale;
}

/// 3차원 벡터의 산술, 내적, 외적 및 거리 계산을 제공한다.
template<typename T>
class vector3d
{
public:
    using length_type = vector_length_t<T>;

    constexpr vector3d() = default;
    constexpr vector3d(T x, T y, T z) : X(x), Y(y), Z(z) {}

    constexpr vector3d operator+(const vector3d& rhs) const { return {X + rhs.X, Y + rhs.Y, Z + rhs.Z}; }
    constexpr vector3d operator-(const vector3d& rhs) const { return {X - rhs.X, Y - rhs.Y, Z - rhs.Z}; }
    constexpr vector3d operator*(T scale) const { return {X * scale, Y * scale, Z * scale}; }

    constexpr length_type dot(const vector3d& rhs) const
    {
        return static_cast<length_type>(X) * rhs.X +
            static_cast<length_type>(Y) * rhs.Y + static_cast<length_type>(Z) * rhs.Z;
    }
    constexpr vector3d cross(const vector3d& rhs) const
    {
        return {Y * rhs.Z - Z * rhs.Y, Z * rhs.X - X * rhs.Z, X * rhs.Y - Y * rhs.X};
    }
    constexpr length_type getLengthSquared() const { return dot(*this); }
    length_type getLength() const
    {
        return std::hypot(static_cast<length_type>(X), static_cast<length_type>(Y), static_cast<length_type>(Z));
    }

    // A zero vector remains zero; normalization does not modify the original.
    vector3d<length_type> normalize() const
    {
        const auto length = getLength();
        return length > 0 && std::isfinite(length)
            ? vector3d<length_type>{X / length, Y / length, Z / length}
            : vector3d<length_type>{};
    }

    T X{}, Y{}, Z{};
};

template<typename T>
constexpr vector3d<T> operator*(T scale, const vector3d<T>& value)
{
    return value * scale;
}

/// 화면 또는 평면 좌표의 두 성분을 보관하는 값 타입이다.
template<typename T>
class position2d
{
public:
    constexpr position2d() = default;
    constexpr position2d(T x, T y) : X(x), Y(y) {}

    T X{}, Y{};
};

/// 공간 좌표의 세 성분을 보관하는 값 타입이다.
template<typename T>
class position3d
{
public:
    constexpr position3d() = default;
    constexpr position3d(T x, T y, T z) : X(x), Y(y), Z(z) {}

    T X{}, Y{}, Z{};
};

/// 2차원 선분의 양 끝점과 길이 계산을 제공한다.
template<typename T>
class line2d
{
public:
    vector2d<T> start, end;

    vector_length_t<T> getLength() const
    {
        using R = vector_length_t<T>;
        return std::hypot(static_cast<R>(end.X) - start.X, static_cast<R>(end.Y) - start.Y);
    }
};

/// 3차원 선분의 양 끝점과 길이 계산을 제공한다.
template<typename T>
class line3d
{
public:
    vector3d<T> start, end;

    vector_length_t<T> getLength() const
    {
        using R = vector_length_t<T>;
        return std::hypot(static_cast<R>(end.X) - start.X,
            static_cast<R>(end.Y) - start.Y, static_cast<R>(end.Z) - start.Z);
    }
};

/// 기본 이벤트 데이터를 보관하는 공통 구조체이다.
struct SEvent
{
    s32 a;
};

typedef vector2d<s32> vector2di;
typedef vector3d<s32> vector3di;
typedef vector2d<f32> vector2df;
typedef vector3d<f32> vector3df;
typedef line2d<f32> line2df;
typedef line3d<f32> line3df;

typedef position2d<s16> position2di;
typedef position3d<s16> position3di;
