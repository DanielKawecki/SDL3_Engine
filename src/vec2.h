#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#define M_PI 3.14159265358979323846

class vec2 {
public:

	float x, y;

	vec2() : x(0.f), y(0.f) {}
	vec2(float x) : x(x), y(x) {}
	vec2(float x, float y) : x(x), y(y) {}


	vec2& operator=(const vec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}


	vec2 operator+(vec2& v) {
		return vec2(x + v.x, y + v.y);
	}
	vec2 operator-(vec2& v) {
		return vec2(x - v.x, y - v.y);
	}


	vec2& operator+=(vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	vec2& operator-=(vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}


	vec2 operator+(float s) {
		return vec2(x + s, y + s);
	}
	vec2 operator-(float s) {
		return vec2(x - s, y - s);
	}
	vec2 operator*(float s) {
		return vec2(x * s, y * s);
	}
	vec2 operator/(float s) {
		return vec2(x / s, y / s);
	}


	vec2& operator+=(float s) {
		x += s;
		y += s;
		return *this;
	}
	vec2& operator-=(float s) {
		x -= s;
		y -= s;
		return *this;
	}
	vec2& operator*=(float s) {
		x *= s;
		y *= s;
		return *this;
	}
	vec2& operator/=(float s) {
		x /= s;
		y /= s;
		return *this;
	}


	float length() const {
		return std::sqrt(x * x + y * y);
	}

	vec2& normalize() {
		if (length() == 0.f) return *this;
		*this *= (1.f / length());
		return *this;
	}
};

#endif // !VEC2_H
