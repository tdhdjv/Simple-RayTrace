#pragma once

#include "core.h"
#include <cmath>

struct interval {
	double max;
	double min;

	interval(double min, double max) :min(min), max(max) {};

	double size() const {
		return max - min;
	}

	bool contains(float f) const {
		return min <= f && f <= max;
	}

	bool surrounds(float f) const {
		return min < f && f < max;
	}

	static const interval empty, universe;
};

const interval interval::empty = interval(+inf, -inf);
const interval interval::universe = interval(-inf, +inf);

double clamp(float a, float min, float max) {
	return std::fmin(std::fmax(a, min), max);
}

