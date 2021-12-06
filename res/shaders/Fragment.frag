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
	vec2 start;
	vec2 end;
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
	float x2 = ray.start.x + 200 * cos(radians(ray.angle));
	float y2 = ray.start.y + 200 * sin(radians(ray.angle));
	vec2 p1 = ray.start;
	vec2 p2 = (ray.angle < -360) ? ray.end: vec2(x2, y2);
	vec2 p3 = {x, y};

	vec2 p12 = p2 - p1;
	vec2 p13 = p3 - p1;
	float d = dot(p12, p13) / length(p12);
	vec2 p14 = d * normalize(p12);
	vec2 p24 = p14 + p1 - p2;
	if (length(p13 - p14) <= RAY_THICCNESS && length(p14) <= length(p12) && length(p24) <= length(p12))
		out_color = vec4(0.0, 0.0, 1.0, 1.0);
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
