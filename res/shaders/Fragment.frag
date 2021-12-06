#version 430 core

precision mediump float;

struct Circle
{
	float x;
	float y;
	float radius;
};
uniform int numberCircles;
uniform Circle circles[100];

uniform struct Ray
{
	float x;
	float y;
	float angle;
} ray;
//uniform int numberRays;
//uniform Ray rays[100];

out vec4 out_color;

#define RAY_THICCNESS 5

void drawCircle(float x, float y, float radius)
{
	if (pow(gl_FragCoord.xy.x - x, 2) + pow(gl_FragCoord.xy.y - y, 2) <= pow(radius, 2))
		out_color = vec4(1.0, 0.0, 0.0, 1.0);
}


void drawRay(Ray ray)
{
	float x = gl_FragCoord.x;
	float y = gl_FragCoord.y;
	float x1 = ray.x;
	float y1 = ray.y;
	float x2 = x1 + 200 * cos(radians(ray.angle));
	float y2 = y1 + 200 * sin(radians(ray.angle));
	if (sign(y2 - y) == sign(y - y1) &&
		sign(x2 - x) == sign(x - x1)) {
		float distance = (y - y1) * cos(radians(ray.angle)) - (x - x1) * sin(radians(ray.angle));
		if (abs(distance) <= RAY_THICCNESS) {
			out_color = vec4(0.0, 0.0, 1.0, 1.0);
		}
	}
}

void main(void)
{
	// Set the background color.
	out_color = vec4(0.0, 0.0, 0.0, 1.0);

	for (int i = 0; i < numberCircles; i++) {
		drawCircle(circles[i].x, circles[i].y, circles[i].radius);
	}

	drawRay(ray);
}
