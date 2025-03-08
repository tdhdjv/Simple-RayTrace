#pragma once

#include <iostream>
#include "interval.h"
#include "vec3.h"

using color = vec3;

double gammaCorrection(double component) {
	return std::sqrt(component);
}

void writeColor(std::ostream& out, const color& pixel_color) {
	double r = clamp(pixel_color.x(), 0.0, 1.0);
	double g = clamp(pixel_color.y(), 0.0, 1.0);
	double b = clamp(pixel_color.z(), 0.0, 1.0);

	r = gammaCorrection(r);
	g = gammaCorrection(g);
	b = gammaCorrection(b);

	int rByte = int(r * 255.999);
	int gByte = int(g * 255.999);
	int bByte = int(b * 255.999);
	
	out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}