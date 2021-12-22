#include "ReflectGUI.h"
#include "ReflectRNG/Scene.h"

#define DEFAULT_SCREEN_WIDTH 1600
#define DEFAULT_SCREEN_HEIGHT 900
#define VERTEX_SHADER_FILENAME "res/shaders/Vertex.vert"
#define FRAGMENT_SHADER_FILENAME "res/shaders/Fragment.frag"

int main(void)
{
	int circleRadius = 60;
	std::vector<Circle> circles { Circle({ 1000, 100 }, circleRadius),
		                          Circle({ 1000, 300 }, circleRadius),
		                          Circle({ 1000, 500 }, circleRadius),
		                          Circle({ 1000, 700 }, circleRadius),
		                          Circle({ 1000, 900 }, circleRadius),
		                          Circle({ 1200, 000 }, circleRadius),
		                          Circle({ 1200, 200 }, circleRadius),
		                          Circle({ 1200, 400 }, circleRadius),
		                          Circle({ 1200, 600 }, circleRadius),
		                          Circle({ 1200, 800 }, circleRadius),
		                          Circle({ 1400, 100 }, circleRadius),
		                          Circle({ 1400, 300 }, circleRadius),
		                          Circle({ 1400, 500 }, circleRadius),
		                          Circle({ 1400, 700 }, circleRadius),
		                          Circle({ 1400, 900 }, circleRadius) };
	Ray ray = Ray({ 400, 450 }, 50);
	Scene scene = Scene(circles, ray);

	int initialised;
	auto app = ReflectGUI(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, VERTEX_SHADER_FILENAME, FRAGMENT_SHADER_FILENAME, initialised);
	if (initialised < 0)
		return -1;
	app.runProgramLoop(scene);
	return 0;
}
