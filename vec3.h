#pragma once

#include <iostream>
#include <cmath>

struct vec3 {
	double e[3];

	vec3() : e{ 0.0, 0.0, 0.0 } {};
	vec3(double e1) : e{ e1, e1, e1 } {};
	vec3(double e1, double e2, double e3) : e{ e1, e2, e3 } {};

	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }

	vec3& operator+=(const vec3& other) {
		e[0] += other.e[0];
		e[1] += other.e[1];
		e[2] += other.e[2];
		return *this;
	}

	vec3& operator-=(const vec3& other) {
		e[0] += other.e[0];
		e[1] += other.e[1];
		e[2] += other.e[2];
		return *this;
	}

	vec3& operator*=(double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(double t) {
		return *this *= 1/t;
	}


	double length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
};


using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator + (const vec3& a, const vec3& b) {
	return vec3(a.e[0] + b.e[0], a.e[1] + b.e[1], a.e[2] + b.e[2]);
}

inline vec3 operator - (const vec3& a) {
	return vec3(-a.e[0], -a.e[1], -a.e[2]);
}

inline vec3 operator - (const vec3& a, const vec3& b) {
	return vec3(a.e[0] - b.e[0], a.e[1] - b.e[1], a.e[2] - b.e[2]);
}

inline vec3 operator * (double t, const vec3& a) {
	return vec3(a.e[0]*t, a.e[1]*t, a.e[2]*t);
}

inline vec3 operator * (const vec3& a, const vec3& b) {
	return vec3(a.e[0] * b.e[0], a.e[1] * b.e[1], a.e[2] * b.e[2]);
}

inline vec3 operator * (const vec3& a, double t) {
	return t * a;
}

inline vec3 operator / (const vec3& a, double t) {
	return (1 / t) * a;
}


inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 normalize(const vec3& v) {
	return v / v.length();
}

inline vec3 reflect(const vec3& a, const vec3& normal) {
	vec3 b = (dot(a, normal) * normal) / normal.length_squared();
	return a - 2*b;
}

inline vec3 randomUnitVector() {
	//just for safety
	for (int i = 0; i < 10; i++) {
		vec3 randVec = vec3(random(-1, 1), random(-1, 1), random(-1, 1));
		double length = randVec.length();
		if (1e-160 < length && length <= 1) {
			return randVec / length;
		}
	}
	return vec3(1.0, 0.0, 0.0);
}

inline vec3 randomUnitVecInHemisphere(const vec3& normal) {
	vec3 randUnit = randomUnitVector();

	if (dot(normal, randUnit) < 0) {
		return -randUnit;
	}
	return randUnit;
}