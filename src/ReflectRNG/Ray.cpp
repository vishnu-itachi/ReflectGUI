#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

#include "Scene.h"

std::optional<std::pair<Point, Circle>> Ray::getFirstIntersection(std::vector<Circle> circles)
{
	Point firstIntersection;
	Circle intersectionCircle;
	float minDistance = FLT_MAX;
	for (auto &circle : circles) {
		if (abs((start - circle.center).length() - circle.radius) < 0.01) continue;
		for (auto &intersection : circle.getIntersections(*this)) {
			if (minDistance <= (start - intersection).length()) continue;
			minDistance = (start - intersection).length();
			firstIntersection = intersection;
			intersectionCircle = circle;
		}
	}
	return (minDistance == FLT_MAX) ? std::optional<std::pair<Point, Circle>>()
	                                : std::make_pair(firstIntersection, intersectionCircle);
}
