#include <vector>
#include <cmath>


#include "Scene.h"

inline float getDistance(Point point1, Point point2)
{
	return std::sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

std::optional<Point> Ray::getFirstIntersection(std::vector<Circle> circles)
{
	Point firstIntersection;
	float minDistance = FLT_MAX;
	for (auto& circle : circles) {
		for (auto& intersection : circle.getIntersections(*this)) {
			if (minDistance > getDistance(start, intersection)) {
				minDistance = getDistance(start, intersection);
				firstIntersection = intersection;
			}
		}
	}
	return (minDistance == FLT_MAX) ? std::optional<Point>() : firstIntersection;
}
