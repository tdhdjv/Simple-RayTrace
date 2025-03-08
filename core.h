#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <memory>

// Constants
const double inf = std::numeric_limits<double>::infinity();
#define PI 3.1415926535897932385

// Utility Functions
inline double degrees_to_radians(double degrees) {
	return degrees * PI / 180.0;
}

inline double random() {
	return std::rand() / (RAND_MAX + 1.0);
}

inline double random(double min, double max) {
	double t = random();
	return min * t + max * (1.0 - t);
}

#include "interval.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"