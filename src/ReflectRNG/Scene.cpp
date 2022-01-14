#include <cmath>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "Scene.h"

float getSlope(std::tuple<float, float> point1, std::tuple<float, float> point2)
{
	return std::get<1>(point1) - std::get<1>(point2) / std::get<0>(point1) - std::get<0>(point2);
}

bool Scene::calculateNextRay()
{
	Ray currentRay = rays.back();
	rays.pop_back();
	// Change the Current Ray's end point and make it a line segment.
	std::optional<std::pair<Point, Circle>> intersection = currentRay.getFirstIntersection(circles);
	if (!intersection.has_value()) {
		rays.push_back(currentRay);
		return false;
	}
	currentRay.end = intersection.value().first;
	currentRay.angle = -400;
	rays.push_back(currentRay);

	// Add the new Reflected Ray to the end of rays.
	Point intersectionPoint = intersection.value().first;
	Circle circle = intersection.value().second;

	Point p21 = currentRay.start - intersectionPoint;
	Point p32 = intersectionPoint - circle.center;
	float d = p21.length();
	float cos = p21.dot(p32) / (d * circle.radius);
	float numer = 2 * cos * d * (p32.y) - circle.radius * (p21.y);
	float denom = 2 * cos * d * (p32.x) - circle.radius * (p21.x);
	float angle = atan2(numer, denom) * 180 / PI;
	Ray newRay = Ray(intersectionPoint, angle);
	rays.push_back(newRay);
	return true;
}

void Scene::calculateAllRays()
{
	while (calculateNextRay()) { }
}

void Scene::drawScene(GLFWwindow *window, int program, int screenWidth, int screenHeight)
{
	double posx, posy;
	glfwGetCursorPos(window, &posx, &posy);
	Ray ray = this->rays[0];
	float angle = atan2(screenHeight - posy - ray.start.y, posx - ray.start.x) * 180 / PI;
	ray.angle = (int) angle;
	this->rays.clear();
	this->rays.push_back(ray);
	this->calculateAllRays();

	glUniform1i(glGetUniformLocation(program, "numberCircles"), this->circles.size());
	for (int i = 0; i < this->circles.size(); i++) {
		glUniform1f(glGetUniformLocation(program, ("circles[" + std::to_string(i) + "].x").c_str()), this->circles[i].center.x);
		glUniform1f(glGetUniformLocation(program, ("circles[" + std::to_string(i) + "].y").c_str()), this->circles[i].center.y);
		glUniform1f(glGetUniformLocation(program, ("circles[" + std::to_string(i) + "].radius").c_str()), this->circles[i].radius);
	}
	glUniform1i(glGetUniformLocation(program, "numberRays"), this->rays.size());
	for (int i = 0; i < this->rays.size(); i++) {
		glUniform2f(glGetUniformLocation(program, ("rays[" + std::to_string(i) + "].start").c_str()), this->rays[i].start.x, this->rays[i].start.y);
		glUniform2f(glGetUniformLocation(program, ("rays[" + std::to_string(i) + "].end").c_str()), this->rays[i].end.x, this->rays[i].end.y);
		glUniform1f(glGetUniformLocation(program, ("rays[" + std::to_string(i) + "].angle").c_str()), this->rays[i].angle);
	}
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
}
