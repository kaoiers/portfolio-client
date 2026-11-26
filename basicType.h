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

#define SAFE_DELETE(a) if(a!=0) delete a

typedef short s16;
typedef int s32;
typedef float f32;
typedef unsigned int u32;

template<typename T>
class vector2d
{
public:
    vector2d() {}
    vector2d(T _x, T _y) : X(_x), Y(_y) {};

    T X, Y;
};

template<typename T>
class vector3d
{
public:
    vector3d() {}

    vector3d(T _x, T _y, T _z) : X(_x), Y(_y), Z(_z) {};

    T getLength() const { return 1; }
    const vector3d<T> normalize() const { return *this; }

    vector3d<T> operator*(const T& a)
    {
        return *this;
    }

    T X, Y, Z;
};

template<typename T>
vector3d<T> operator+(const vector3d<T>& a, const vector3d<T>& b)
{
    return a;
}

template<typename T>
vector3d<T> operator-(const vector3d<T>& a, const vector3d<T>& b)
{
    return a;
}

template<typename T>
const vector3d<T> operator*(const T& a, const vector3d<T>& b)
{
    return b;
}

template<typename T>
class position2d
{
public:
    position2d() {}
    position2d(T _x, T _y) : X(_x), Y(_y) {};

    T X, Y;
};

template<typename T>
class position3d
{
public:
    position3d(T _x, T _y, T _z) : X(_x), Y(_y), Z(_z) {};

    T X, Y, Z;
};

template<typename T>
class line2d
{
public:
    line2d() {}
    vector2d<T> start, end;

    T getLength() const { return 0; }
};

template<typename T>
class line3d
{
public:
    line3d() {}
    vector3d<T> start, end;
    T getLength() const { return 0; }
};

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
