#pragma once

#include "hittable.h"
#include "core.h"

struct material {
	color albedo;
	double metallic;
	material():albedo(1.0), metallic(0.0) {}
	material(color albedo, double metallic) :albedo(albedo), metallic(metallic) {}
};