#pragma once

#include "vec3.h"

struct ray {
public:
	ray(): orig(), dir() {}
	ray(const vec3& origin, const vec3& direction): orig(origin), dir(direction) {}

	vec3 at(double t) {
		return orig + t * dir;
	}

	inline const point3& origin() const { return orig; }
	inline const vec3& direction() const { return dir; }
private:
	vec3 orig;
	vec3 dir;
};