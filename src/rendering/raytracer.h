#if !defined(RAYTRACER_H)
#define RAYTRACER_H

#include <iostream>
#include <sstream>
#include <vector>

#include "camera/camera.h"
#include "materials/material.h"
#include "objects/sphere.h"
#include "rendering/hitable_list.h"
#include "types/types.h"
#include "types/vec2.h"
#include "types/vec3.h"

// Move this eventually to types
inline vec3 color(const ray &r, hitable *world, int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, std::numeric_limits<double>::max(), rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		} else {
			return vec3(0, 0, 0);
		}
	} else {
		vec3 unit_direction = unit_vector(r.direction());
		double t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

// determine the size of the pixel

class raytracer {
public:
	raytracer(){};
	std::stringstream renderPPM(camera *cam, vec2<int> res, int samples,
	                            std::vector<hitable *> elements);

	std::vector<pixel> render(camera *cam, vec2<int> res, int samples,
	                          std::vector<hitable *> elements);
};

#endif // RAYTRACER_H