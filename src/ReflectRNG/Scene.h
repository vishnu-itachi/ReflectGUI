#pragma once
class Ray
{
public:
	std::tuple <float, float> start;
	std::tuple <float, float> end;
	float angle = NULL;

	Ray(std::tuple <float, float> start, float angle)
		:start(start), angle(angle) {}

	Ray(std::tuple <float, float> start, std::tuple <float, float> end)
		:start(start), end(end) {}

	std::tuple <float, float> getFirstIntersection(std::vector<Circle> circles);
};

class Circle
{
public:
	std::tuple <float, float> position;
	float radius;

	Circle(std::tuple <float, float> position, float radius)
		:position(position), radius(radius) {}
	std::vector< std::tuple <float, float>> getIntersections(Ray ray);
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
