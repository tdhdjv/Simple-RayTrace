#include "core.h"

#include "camera.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"

hittableList world;

int main() {
	const int sampleForPixel = 10;
	const double sampleScale = 1 / double(sampleForPixel);
	std::ofstream imageFile("image.ppm");

	//hittable list

	std::shared_ptr<material> mat1 = std::make_shared<material>(color(1.0, 1.0, 1.0), 1.0);
	std::shared_ptr<material> mat2 = std::make_shared<material>(color(0.9), 0.0);
	std::shared_ptr<material> mat3 = std::make_shared<material>(color(0.0, 0.9, 0.0), 0.0);
	std::shared_ptr<material> mat4 = std::make_shared<material>(color(0.9, 0.0, 0.0), 0.0);
	
	world.add(std::make_shared<sphere>(vec3(0.0, 0.0, -3.0), 1.0, mat1));
	world.add(std::make_shared<sphere>(vec3(2.0, 0.0, -2.0), 0.5, mat2));
	world.add(std::make_shared<sphere>(vec3(-2.0, 0.0, -3.0), 1.0, mat3));
	world.add(std::make_shared<sphere>(vec3(-1.0, 1.0, -5.0), 2.0, mat3));
	world.add(std::make_shared<plane>(vec3(0.0, -1.0, 0.0), vec3(0.0, 1.0, 0.0), mat4));

	//Camera
	camera cam(16.0 / 9.0, 400);
	
	cam.render(world);

	std::cin.get();

	imageFile.close();
}