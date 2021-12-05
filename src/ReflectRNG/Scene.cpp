#include <tuple>
#include <vector>
#include "Circle.cpp"
#include "Ray.cpp"

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

	void calculateNextRay()
	{
		Ray currentRay = rays.back();
		// Calculate the current ray's intersection with the circles and add the new ray to the scene.
	}


};