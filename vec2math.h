//
// Created by Neko on 10/10/2023.
//
#pragma once




#ifdef _gcem_HPP
#define DEFINED
#define ENABLE_CONSTEXPR
#define _sin(x)      gcem::sin(x)
#define _cos(x)      gcem::cos(x)
#define _acos(x)     gcem::acos(x)
#define _atan2(x,y)  gcem::atan2(x,y)
#define _sqrt(x)     gcem::sqrt(x)
#endif

#ifndef DEFINED
#include <cmath>
#define _sin(x)      sin(x)
#define _cos(x)      cos(x)
#define _acos(x)     acos(x)
#define _atan2(x,y)  atan2(x,y)
#define _sqrt(x)     sqrt(x)
#endif




#ifdef ENABLE_CONSTEXPR
#define maybe_constexpr constexpr
static constexpr bool IS_CONSTEXPR_MATH_ENABLED = true;
#else
#define maybe_constexpr
static constexpr bool IS_CONSTEXPR_MATH_ENABLED = false;
#endif
#undef ENABLE_CONSTEXPR
#undef DEFINED


namespace vec2math{



    using decimal_type = float;


    constexpr decimal_type ToDegrees(decimal_type rad) { return 180*rad/3.141592653f; }
    constexpr decimal_type ToRadians(decimal_type degrees){ return degrees*3.141592653f/180; }


    template<typename T>
    class Vec2{
    public:

        T x;
        T y;

        constexpr Vec2() noexcept : x(0), y(0)  {}
        constexpr Vec2(T _x, T _y) noexcept : x(_x), y(_y) {}
        constexpr Vec2(const Vec2& vec) noexcept : x(vec.x), y(vec.y) {}

        static constexpr       Vec2 Add(const Vec2& v1, const Vec2& v2)      { return Vec2(v1 + v2); }
        static constexpr       Vec2 Sub(const Vec2& v1, const Vec2& v2)      { return Vec2(v1 - v2); }
        static constexpr       Vec2 Mult(const Vec2& v, decimal_type scalar) { return Vec2(v * scalar); }
        static constexpr       Vec2 Div(const Vec2& v, decimal_type scalar)  { return Vec2(v / scalar); }
        static maybe_constexpr Vec2 FromAngle(decimal_type theta)            { return Vec2(_cos(theta), _sin(theta)); }


        static constexpr       decimal_type Dot(const Vec2& v1, const Vec2& v2)          { return v1.x*v2.x+v1.y*v2.y; }
        static constexpr       decimal_type MagSq(const Vec2& v)                         { return v.x*v.x+v.y*v.y; }
        static maybe_constexpr decimal_type Mag(const Vec2& v)                           { return _sqrt(v.x*v.x+v.y*v.y); }
        static maybe_constexpr decimal_type Heading(const Vec2& v)                       { return _atan2(v.x,v.y); }
        static maybe_constexpr decimal_type AngleBetween(const Vec2& v1, const Vec2& v2) { return _acos( v1.dot(v2) / (v1.mag()*v2.mag()) ); }


        [[maybe_unused]] constexpr Vec2& add(const Vec2& vec)        noexcept { x+=vec.x; y+=vec.y; return *this; }
        [[maybe_unused]] constexpr Vec2& sub(const Vec2& vec)        noexcept { x-=vec.x; y-=vec.y; return *this; }
        [[maybe_unused]] constexpr Vec2& mult(decimal_type scalar)   noexcept { x*=scalar; y*=scalar; return *this; }
        [[maybe_unused]] constexpr Vec2& div(decimal_type scalar)    noexcept { if(scalar != 0) { x /= scalar; y /= scalar; } return *this; }
        [[maybe_unused]] constexpr Vec2& normalize()                 noexcept { if(decimal_type m = mag(); m != 0) div(m); return *this; }
        [[maybe_unused]] constexpr Vec2& limit(decimal_type ammount) noexcept { if(decimal_type m = mag(); m != 0) mult((m < ammount ? m : ammount) / m); return *this; }
        [[maybe_unused]] constexpr Vec2& lerp(const Vec2& vmin,const Vec2& vmax, float t) noexcept{
            if(t > 0 && t < 1){
                x = vmin.x+t*(vmax.x-vmin.x);
                y = vmin.y+t*(vmax.y-vmin.y);
            }else
                if(t <= 0) { x = vmin.x; y = vmin.y; } else
                if(t >= 1) { x = vmax.x; y = vmax.y; }
            return *this;
        }

        constexpr decimal_type dot(Vec2 v)                       const noexcept { return x*v.x+y*v.y; }
        constexpr decimal_type magSq()                           const noexcept { return x*x+y*y; }
        maybe_constexpr decimal_type mag()                       const noexcept { return _sqrt(x*x+y*y); }
        maybe_constexpr decimal_type heading()                   const noexcept { return _atan2(x,y); }
        maybe_constexpr decimal_type angleBetween(const Vec2& v) const noexcept { return _acos( dot(v) / (mag()*v.mag()) ); }



    };




    template<typename T> static constexpr Vec2<T> operator+(Vec2<T> v1, Vec2<T> v2){ return Vec2(v1.x + v2.x, v1.y + v2.y); }
    template<typename T> static constexpr Vec2<T> operator-(Vec2<T> v1, Vec2<T> v2){ return Vec2(v1.x - v2.x, v1.y - v2.y); }
    template<typename T> static constexpr Vec2<T> operator*(Vec2<T> v, decimal_type scalar){ return Vec2(v.x * scalar, v.y * scalar); }
    template<typename T> static constexpr Vec2<T> operator/(Vec2<T> v, decimal_type scalar){ return Vec2(v.x / scalar, v.y / scalar); }


}

typedef vec2math::Vec2<int> Vec2;
typedef vec2math::Vec2<float> Vec2f;

#include <ostream>
template<typename T> static constexpr std::ostream& operator <<(std::ostream& cout, vec2math::Vec2<T>& vec) { return cout << "{" << vec.x << ',' << vec.y << "}"; }
