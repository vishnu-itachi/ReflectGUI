#include <tuple>
#include <vector>
#include <cmath>

#include "Scene.h"


float getSlope(std::tuple <float, float> point1, std::tuple <float, float> point2)
{
	return std::get<1>(point1) - std::get<1>(point2) / std::get<0>(point1) - std::get<0>(point2);
}

void Scene::calculateNextRay()
{
	Ray currentRay = rays.back();
	// Calculate the current ray's intersection with the circles and add the new ray to the scene.
	std::tuple <float, float> intersection = currentRay.getFirstIntersection(circles);
	// Calculate the angle of the reflected ray.
	//float m1 = getSlope(intersection, currentRay.start);
	//float m2 = getSlope(intersection, currentRay.start);
}

void Scene::calculateAllRays()
{

}
