#include <tuple>
#include <vector>
#include <cmath>
#include <iostream>

#include "Scene.h"


float getSlope(std::tuple <float, float> point1, std::tuple <float, float> point2)
{
	return std::get<1>(point1) - std::get<1>(point2) / std::get<0>(point1) - std::get<0>(point2);
}

bool Scene::calculateNextRay()
{
	Ray currentRay = rays.back();
	rays.pop_back();
	// Change the Current Ray's end point and make it a line segment.
	std::optional<std::pair<Point, Circle>> intersection = currentRay.getFirstIntersection(circles);
	if (intersection.has_value()) {
		currentRay.end = intersection.value().first;
		currentRay.angle = -400;
		rays.push_back(currentRay);
		
		// Add the new Reflected Ray to the end of rays.
		Point intersectionPoint = intersection.value().first;
		Circle circle = intersection.value().second;
		
		Point p21 = currentRay.start - intersectionPoint;
		Point p32 = intersectionPoint - circle.center;
		float d = p21.length();
		//std::cout << circle.center.x << " " << circle.center.y << " " << circle.radius << std::endl;
		//std::cout << d << " " << intersectionPoint.x << " " << intersectionPoint.y << std::endl;
		float cos = p21.dot(p32) / (d * circle.radius);
		float numer = 2 * cos * d * (p32.y) - circle.radius * (p21.y);
		float denom = 2 * cos * d * (p32.x) - circle.radius * (p21.x);
		float angle = atan2(numer, denom) * 180 / PI;
		//std::cout << cos << " " << numer << " " << denom << " " << numer/denom << " " << angle << std::endl;
		Ray newRay = Ray(intersectionPoint, angle);
		rays.push_back(newRay);
		return true;
	}
	rays.push_back(currentRay);
	return false;
}

void Scene::calculateAllRays()
{
	while (calculateNextRay()) {
		Ray currentRay = rays.back();
		std::cout << currentRay.angle << std::endl;
	}
}
