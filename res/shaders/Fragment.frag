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

out vec4 out_color;

//#define VEC4_NULL vec4(-1.0, 0.0, 0.0, 0.0)

void drawCircle(float x, float y, float radius)
{
	if (pow(gl_FragCoord.xy.x - x, 2) + pow(gl_FragCoord.xy.y - y, 2) <= pow(radius, 2))
		out_color = vec4(1.0, 0.0, 0.0, 1.0);
}

void main(void)
{
	// Set the background color.
	out_color = vec4(0.0, 0.0, 0.0, 1.0);

	for (int i = 0; i < numberCircles; i++) {
		drawCircle(circles[i].x, circles[i].y, circles[i].radius);
	}
}
