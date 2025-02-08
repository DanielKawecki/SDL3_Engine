#pragma once
#include <cmath>

namespace mth {

    struct ivec2 {
        int x, y;
    };

    struct vec2 {
        float x = 0, y = 0;

        constexpr vec2() = default;
        constexpr vec2(float x, float y) : x(x), y(y) {}
    };

    inline vec2 operator+(const vec2& lhs, const vec2& rhs) {
        return { lhs.x + rhs.x, lhs.y + rhs.y };
    }

    inline vec2 operator-(const vec2& lhs, const vec2& rhs) {
        return { lhs.x - rhs.x, lhs.y - rhs.y };
    }

    template<typename T>
    inline vec2 operator*(const vec2& lhs, T rhs) {
        return { lhs.x * rhs, lhs.y * rhs };
    }

    template<typename T>
    inline vec2 operator*(T lhs, const vec2& rhs) {
        return { lhs * rhs.x, lhs * rhs.y };
    }

    template<typename T>
    inline vec2 operator/(const vec2& lhs, T rhs) {
        if (rhs == 0) return { 0, 0 }; // Prevent division by zero
        return { lhs.x / rhs, lhs.y / rhs };
    }

    template<typename T>
    inline vec2 operator+=(const vec2& lhs, T rhs) {
        return { lhs.x + rhs, lhs.y + rhs };
    }

    template<typename T>
    inline vec2 operator-=(const vec2& lhs, T rhs) {
        return { lhs.x - rhs, lhs.y - rhs };
    }

    inline float length(const vec2& v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    inline vec2 normalize(const vec2& v) {
        float len = length(v);
        return (len == 0.f) ? vec2{ 0, 0 } : vec2{ v.x / len, v.y / len };
    }

    inline float dot(const vec2& a, const vec2& b) {
        return a.x * b.x + a.y * b.y;
    }

    inline vec2 perpendicular(const vec2& v) {
        return { -v.y, v.x }; // 90-degree rotation
    }

    inline bool operator==(const vec2& lhs, const vec2& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    inline bool operator!=(const vec2& lhs, const vec2& rhs) {
        return !(lhs == rhs);
    }

}
