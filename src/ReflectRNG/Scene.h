#pragma once
#include <optional>

class Circle;
class Ray;

class Point
{
public:
	float x;
	float y;
};

class Ray
{
public:
	Point start;
	Point end;
	float angle = NULL;

	Ray(Point start, float angle)
		:start(start), angle(angle) {}

	Ray(Point start, Point end)
		:start(start), end(end) {}

	std::optional<Point> getFirstIntersection(std::vector<Circle> circles);
};

class Circle
{
public:
	Point center;
	float radius;

	Circle(Point center, float radius)
		:center(center), radius(radius) {}
	std::vector<Point> getIntersections(Ray ray);
};

class Scene
{
public:
	std::vector<Circle> circles;
	std::vector<Ray>  rays;

	Scene(std::vector<Circle> circles, std::vector<Ray> rays)
		:circles(circles), rays(rays) {}

	Scene(std::vector<Circle> circles, Ray ray)
		:circles(circles)
	{
		rays.push_back(ray);
	}

	void calculateNextRay();
	void calculateAllRays();
};
