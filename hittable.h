#pragma once

#include "material.h"
#include "core.h"

struct hitPoint {
	point3 point;
	std::shared_ptr<material> mat;
	vec3 normal;
	double t;
};

struct hittable {
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, interval range, hitPoint& hitP) const = 0;
};

struct sphere: public hittable {
public:
	sphere(vec3 position, double radius, std::shared_ptr<material> mat): position(position), radius(radius), mat(mat) {};

	void setMat(std::shared_ptr<material> newMat) {
		mat = newMat;
	}

	std::shared_ptr<material> getMat() {
		return mat;
	}

	bool hit(const ray& r, interval range, hitPoint& hitP) const override {

		vec3 oc = position - r.origin();
		double a = r.direction().length_squared();
		double h = dot(r.direction(), oc);
		double c = oc.length_squared() - radius * radius;

		double determinance = h * h - a * c;

		if (determinance <= 0) {
			return false;
		}
		double root = (h - std::sqrt(determinance)) / a;
		if (!range.contains(root)) return false;
		hitP.t = root;
		hitP.point = r.origin() + r.direction() * hitP.t;
		hitP.normal = normalize(hitP.point - position);
		hitP.mat = mat;
		return true;
	}

private:
	vec3 position;
	double radius;
	std::shared_ptr<material> mat;
};

struct hittableList : public hittable {
public:

	void clear() { hittableList.clear(); }

	void add(std::shared_ptr<hittable> object) {
		hittableList.emplace_back(object);
	}

	bool hit(const ray& r, interval range, hitPoint& hitP) const override {
		hitPoint h;
		double newMaxT = range.max;

		bool isHitAny = false;
		for (const auto& object : hittableList) {
			bool isHit = object->hit(r, interval(range.min, newMaxT), h);
			if (isHit) {
				isHitAny = true;
				hitP.t = h.t;
				hitP.normal = h.normal;
				hitP.point = h.point;
				hitP.mat = h.mat;
				newMaxT = h.t;
			}
		}

		return isHitAny;
	}

private:
	std::vector<std::shared_ptr<hittable>> hittableList;
};

struct plane : public hittable {
//currently only a xz plane
public:
	plane(vec3 position, vec3 normal, std::shared_ptr<material> mat): position(position), normal(normal), mat(mat) {}
	bool hit(const ray& r, interval range, hitPoint& hitP) const override {
		if (r.direction().y() == 0) { return false; }
		double t = dot(position - r.origin(), normal) / dot(r.direction(), normal);

		point3 p = r.direction() * t + r.origin();
		if (!range.contains(t)) return false;
		hitP.t = t;
		hitP.point = p;
		hitP.normal = vec3(0.0, 1.0, 0.0);
		hitP.mat = mat;
		return true;
	}
private:
	vec3 position;
	vec3 normal;
	std::shared_ptr<material> mat;
};