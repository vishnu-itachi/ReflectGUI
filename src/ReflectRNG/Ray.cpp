#include <tuple>
#include <vector>
#include <cmath>


#include "Scene.h"

float getDistance(std::tuple <float, float> point1, std::tuple <float, float> point2)
{
	return std::sqrt(pow(std::get<0>(point1) - std::get<0>(point2), 2) + pow((std::get<1>(point1) - std::get<1>(point2)), 2));
}

std::tuple <float, float> Ray::getFirstIntersection(std::vector<Circle> circles)
{
	std::tuple <float, float> firstIntersection;
	float minDistance = FLT_MAX;
	for (auto& circle : circles) {
		for (auto& intersection : circle.getIntersections(*this)) {
			if (minDistance < getDistance(start, intersection)) {
				minDistance = getDistance(start, intersection);
				firstIntersection = intersection;
			}
		}
	}
	return firstIntersection;
}
