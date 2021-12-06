#include <tuple>
#include <vector>
#include <cmath>

#include "Scene.h"

std::vector< std::tuple <float, float>> Circle::getIntersections(Ray ray)
{
	float x1 = std::get<0>(ray.start);
	float y1 = std::get<1>(ray.start);
	float dx = cos(ray.angle);
	float dy = sin(ray.angle);
	float D = x1 * dy - y1 * dx;
	if (radius < D)
		return {};
	if (radius == D)
		return { {D * dy, -D * dx} };

	auto sgn = [](float x) -> float {return (x < 0) ? -1 : 1; };
	float x_ = sgn(dy)* dx* std::sqrtf(pow(radius, 2) - pow(D, 2));
	float y_ = std::abs(dx)* std::sqrtf(pow(radius, 2) - pow(D, 2));
	return {
		{D * dy + x_, -D * dx + y_},
		{D * dy - x_, -D * dx - y_}
	};
}
