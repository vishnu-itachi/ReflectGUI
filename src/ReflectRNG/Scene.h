#pragma once
#include <optional>

#define PI 3.141592653589793

class Circle;
class Ray;

class Point
{
public:
	float x;
	float y;

	float length() { return std::sqrt(pow(x, 2) + pow(y, 2)); }
	Point operator + (Point const& right) { return Point(x + right.x, y + right.y); }
	Point operator - (Point const& right) { return Point(x - right.x, y - right.y); }
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

	std::optional<std::pair<Point, Circle>> getFirstIntersection(std::vector<Circle> circles);
};

class Circle
{
public:
	Point center;
	float radius;

	Circle() {}
	Circle(Point center, float radius)
		:center(center), radius(radius) {}
	void operator()(Circle const& obj) { center = obj.center; radius = obj.radius; }
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

	bool calculateNextRay();
	void calculateAllRays();
};
