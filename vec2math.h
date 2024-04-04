//
// Created by Neko on 10/10/2023.
//
#pragma once










namespace vec2math {

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
	
#ifdef __cplusplus 202002L
#define NO_CONCEPTS
#endif

	
#ifdef NO_CONCEPTS
#define NumericType typename
#define DecimalType typename
#else

    template<typename T> concept _NumericType = std::is_arithmetic_v<T>;
    template<typename T = float> concept _DecimalType = std::is_arithmetic_v<T>;
	
#define NumericType _NumericType
#define DecimalType _DecimalType
#endif


    


    template<DecimalType Decimal_t> constexpr Decimal_t ToDegrees(Decimal_t rad) { return 180 * rad / 3.141592653f; }
    template<DecimalType Decimal_t> constexpr Decimal_t ToRadians(Decimal_t degrees) { return degrees * 3.141592653f / 180; }

    
	
    template<NumericType T> 
    class Vec2 {
        static_assert(std::is_arithmetic_v<T>, "arithmetic type required for Vec2.");
    public:
       
        T x;
        T y;

        constexpr Vec2() noexcept : x(0), y(0) {}
        constexpr Vec2(T _x, T _y) noexcept : x(_x), y(_y) {}
        constexpr Vec2(const Vec2& vec) noexcept : x(vec.x), y(vec.y) {}

        static constexpr                                       Vec2 Add(const Vec2& v1, const Vec2& v2) { return Vec2(v1 + v2); }
        static constexpr                                       Vec2 Sub(const Vec2& v1, const Vec2& v2) { return Vec2(v1 - v2); }
        template<DecimalType Decimal_t> static constexpr       Vec2 Mult(const Vec2& v, Decimal_t scalar) { return Vec2(v * scalar); }
        template<DecimalType Decimal_t> static constexpr       Vec2 Div(const Vec2& v, Decimal_t scalar) { return Vec2(v / scalar); }
        template<DecimalType Decimal_t> static maybe_constexpr Vec2 FromAngle(Decimal_t theta) { return Vec2(_cos(theta), _sin(theta)); }


        template<DecimalType Decimal_t> static constexpr       Decimal_t Dot(const Vec2& v1, const Vec2& v2) { return v1.x * v2.x + v1.y * v2.y; }
        template<DecimalType Decimal_t> static constexpr       Decimal_t MagSq(const Vec2& v) { return v.x * v.x + v.y * v.y; }
        template<DecimalType Decimal_t> static maybe_constexpr Decimal_t Mag(const Vec2& v) { return _sqrt(v.x * v.x + v.y * v.y); }
        template<DecimalType Decimal_t> static maybe_constexpr Decimal_t Heading(const Vec2& v) { return _atan2(v.x, v.y); }
        template<DecimalType Decimal_t> static maybe_constexpr Decimal_t AngleBetween(const Vec2& v1, const Vec2& v2) { return _acos(v1.dot(v2) / (v1.mag() * v2.mag())); }


        
        [[maybe_unused]]                                 constexpr Vec2& add(const Vec2& vec)     noexcept { x += vec.x; y += vec.y; return *this; }
        [[maybe_unused]]                                 constexpr Vec2& sub(const Vec2& vec)     noexcept { x -= vec.x; y -= vec.y; return *this; }
        template<DecimalType Decimal_t> [[maybe_unused]] constexpr Vec2& normalize()              noexcept { if (Decimal_t m = mag(); m != 0) div(m); return *this; }
    	template<DecimalType Decimal_t> [[maybe_unused]] constexpr Vec2& mult(Decimal_t scalar)   noexcept { x *= scalar; y *= scalar; return *this; }
    	template<DecimalType Decimal_t> [[maybe_unused]] constexpr Vec2& div(Decimal_t scalar)    noexcept { if (scalar != 0) { x /= scalar; y /= scalar; } return *this; }
        template<DecimalType Decimal_t> [[maybe_unused]] constexpr Vec2& limit(Decimal_t ammount) noexcept { if (Decimal_t m = mag(); m != 0) mult((m < ammount ? m : ammount) / m); return *this; }
        
        [[maybe_unused]] constexpr Vec2& lerp(const Vec2& vmin, const Vec2& vmax, float t) noexcept {
            if (t > 0 && t < 1) {
                x = vmin.x + t * (vmax.x - vmin.x);
                y = vmin.y + t * (vmax.y - vmin.y);
            }
            else
                if (t <= 0) { x = vmin.x; y = vmin.y; }
                else
                    if (t >= 1) { x = vmax.x; y = vmax.y; }
            return *this;
        }

        template<DecimalType Decimal_t> constexpr Decimal_t dot(Vec2 v)                       const noexcept { return x * v.x + y * v.y; }
        template<DecimalType Decimal_t> constexpr Decimal_t magSq()                           const noexcept { return x * x + y * y; }
        template<DecimalType Decimal_t> maybe_constexpr Decimal_t mag()                       const noexcept { return _sqrt(x * x + y * y); }
        template<DecimalType Decimal_t> maybe_constexpr Decimal_t heading()                   const noexcept { return _atan2(x, y); }
        template<DecimalType Decimal_t> maybe_constexpr Decimal_t angleBetween(const Vec2& v) const noexcept { return _acos(dot(v) / (mag() * v.mag())); }

 
        template<typename K> explicit operator K() const { return K{ x,y }; }

    };




    template<NumericType T> static constexpr Vec2<T> operator+(Vec2<T> v1, Vec2<T> v2) { return Vec2(v1.x + v2.x, v1.y + v2.y); }
    template<NumericType T> static constexpr Vec2<T> operator-(Vec2<T> v1, Vec2<T> v2) { return Vec2(v1.x - v2.x, v1.y - v2.y); }
    template<NumericType T, DecimalType Decimal_t> static constexpr Vec2<T> operator*(Vec2<T> v, Decimal_t scalar) { return Vec2(v.x * scalar, v.y * scalar); }
    template<NumericType T, DecimalType Decimal_t> static constexpr Vec2<T> operator/(Vec2<T> v, Decimal_t scalar) { return Vec2(v.x / scalar, v.y / scalar); }

#undef NumericType
#undef DecimalType
#ifdef NO_CONCEPTS
#undef NO_CONCEPTS
#endif

}

typedef vec2math::Vec2<int> Vec2;
typedef vec2math::Vec2<float> Vec2f;

#include <ostream>
template<typename T> static constexpr std::ostream& operator <<(std::ostream& cout, vec2math::Vec2<T>& vec) { return cout << "{" << vec.x << ',' << vec.y << "}"; }
