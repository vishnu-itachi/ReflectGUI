#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

#include "Scene.h"

inline float getDistance(Point point1, Point point2)
{
	return std::sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

std::optional<std::pair<Point, Circle>> Ray::getFirstIntersection(std::vector<Circle> circles)
{
	Point firstIntersection;
	Circle intersectionCircle;
	float minDistance = FLT_MAX;
	for (auto &circle : circles) {
		if (abs((start - circle.center).length() - circle.radius) < 0.01) continue;
		for (auto &intersection : circle.getIntersections(*this)) {
			if (minDistance > getDistance(start, intersection)) {
				minDistance = getDistance(start, intersection);
				firstIntersection = intersection;
				intersectionCircle = circle;
			}
		}
	}
	return (minDistance == FLT_MAX) ? std::optional<std::pair<Point, Circle>>() : std::make_pair(firstIntersection, intersectionCircle);
}
