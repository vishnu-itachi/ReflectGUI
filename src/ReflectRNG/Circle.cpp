#include <cmath>
#include <iostream>
#include <vector>

#include "Scene.h"

std::ostream &operator<<(std::ostream &os, Point const &m)
{
	return os << "(" << m.x << ", " << m.y << ")";
}

std::vector<Point> Circle::getIntersections(Ray ray)
{
	float x1 = ray.start.x - center.x;
	float y1 = ray.start.y - center.y;
	float dx = cos(PI * ray.angle / 180.0);
	float dy = sin(PI * ray.angle / 180.0);
	float D = x1 * dy - y1 * dx;
	Point end = Point(x1 + dx, y1 + dy) + center;
	if ((end - ray.start).dot(center - ray.start) < 0)
		return {};
	if (radius < abs(D))
		return {};
	if (radius == abs(D))
		return { { D * dy + center.x, -D * dx + center.y } };

	auto sgn = [](float x) -> float {
		return (x < 0) ? -1 : 1;
	};
	float x_ = sgn(dy) * dx * std::sqrtf(pow(radius, 2) - pow(D, 2));
	float y_ = std::abs(dy) * std::sqrtf(pow(radius, 2) - pow(D, 2));
	return {
		{ D * dy + x_ + center.x, -D * dx + y_ + center.y },
		{ D * dy - x_ + center.x, -D * dx - y_ + center.y }
	};
}
