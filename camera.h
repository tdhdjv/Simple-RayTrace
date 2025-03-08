#pragma once

#include <fstream>

#include "core.h"
#include "hittable.h"

class camera {
public:

	camera(const double aspectRatio, const int width):
		imageFile("image.ppm"), aspectRatio(aspectRatio),
		imageWidth(width), 
		imageHeight(int(imageWidth / aspectRatio)),
		focalLength(1.0)
	{ 
		viewPortHeight = 2.0;
		viewPortWidth = 2.0 * (double(imageWidth) / imageHeight);
		viewPortU = vec3(viewPortWidth, 0.0, 0.0);
		viewPortV = vec3(0.0, -viewPortHeight, 0.0);
		pixelDeltaU = viewPortU / imageWidth;
		pixelDeltaV = viewPortV / imageHeight;
		viewUpperLeft = position - vec3(0.0, 0.0, focalLength) - (viewPortU + viewPortV) / 2;
		pixelStartPos = viewUpperLeft + (pixelDeltaU + pixelDeltaV) / 2;
	}

	void render(const hittable& world) {

		imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

		for (int i = 0; i < imageHeight; i++) {
			std::cout << "\rScanLines Remaining: " << imageHeight - i << "  " << std::flush;
			for (int j = 0; j < imageWidth; j++) {
				color pixel;
				for (int k = 0; k < sampleCount; k++) {
					ray r = get_ray(i, j);
					pixel += rayColor(r, world, bounceCount) * sampleIntensity;
				}
				writeColor(imageFile, pixel);
			}
		}
		std::cout << "\rDone!                                            " << std::endl;
	};

private:
	std::ofstream imageFile;
	const double aspectRatio;
	
	const int bounceCount = 10;
	const int sampleCount = 50;
	const double sampleIntensity = 1.0 / sampleCount;

	const int imageWidth;
	const int imageHeight;
	
	double viewPortWidth;
	double viewPortHeight;
	
	double focalLength;
	
	vec3 viewPortU;
	vec3 viewPortV;
	
	vec3 pixelDeltaU;
	vec3 pixelDeltaV;

	vec3 viewUpperLeft;
	vec3 pixelStartPos;
	
	point3 position;

	ray get_ray(int i, int j) {
		double offsetX = random(-0.5, 0.5);
		double offsetY = random(-0.5, 0.5);
		vec3 pixelCenter = pixelStartPos + (pixelDeltaU * (j+offsetX)) + (pixelDeltaV * (i+offsetY));
		vec3 rayDir = pixelCenter - position;
		return ray(position, rayDir);

	}

	double func(double x) {
		return (1.0 - x) * (x - 1.0) + 1;
	}

	color rayColor(const ray& r, const hittable& world, int iter) {
		if (iter <= 0) return vec3(0.0);
		color col = vec3(1.0, 1.0, 1.0);
		hitPoint h;
		const double min_t = 0.001;
		const double max_t = 20.0;

		if (world.hit(r, interval(min_t, max_t), h)) {
			vec3 randDir = randomUnitVector() + h.normal;
			vec3 reflectDir = reflect(r.direction(), h.normal);
			vec3 dir = h.mat->metallic * reflectDir + (1.0 - h.mat->metallic) * randDir;
			return h.mat->albedo * rayColor(ray(h.point, dir), world, iter - 1);
		}
		else {
			double a = r.direction().y();
			a = 0.5 * (a + 1.0);
			col = (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
		}
		return col;
	}
};