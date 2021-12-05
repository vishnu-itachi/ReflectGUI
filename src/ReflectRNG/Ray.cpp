#include <tuple>
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
};