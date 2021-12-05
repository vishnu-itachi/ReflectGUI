#include <tuple>
class Circle
{
public:
	std::tuple <float, float> position;
	float radius;

	Circle(std::tuple <float, float> position, float radius)
		:position(position), radius(radius) {}
};