#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ReflectRNG/Scene.h"

#define DEFAULT_SCREEN_WIDTH 1600
#define DEFAULT_SCREEN_HEIGHT 900
#define TIME_STEP 0.005
#define VERTEX_SHADER_FILENAME "res/shaders/Vertex.vert"
#define FRAGMENT_SHADER_FILENAME "res/shaders/Fragment.frag"

static std::string GetShadderFromSource(const std::string &filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss;

	while (getline(stream, line)) {
		ss << line << "\n";
	}

	return ss.str();
}

static unsigned int CompileShader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	/*Error handling*/
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		auto message = (char *) alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertexshader" : "fragmentshader") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string &vertexshader, const std::string &fragmentshader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	int result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		auto message = (char *) alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);

		std::cout << "Failed to link" << std::endl;
		std::cout << message << std::endl;
		return 0;
	}
	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
	if (!result) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		auto message = (char *) alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);

		std::cout << "Failed to link" << std::endl;
		std::cout << message << std::endl;
		return 0;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void runProgram(GLFWwindow *window, unsigned int program)
{

	std::vector<Circle> circles = { Circle({ 500, 500 }, 100),
		                            Circle({ 200, 550 }, 100),
		                            Circle({ 500, 350 }, 100) };
	Ray ray = Ray({ 100, 100 }, 50);
	Scene scene = Scene(circles, ray);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		double posx, posy;
		glfwGetCursorPos(window, &posx, &posy);
		float angle = atan2(DEFAULT_SCREEN_HEIGHT - posy - 100, posx - 100) * 180 / PI;
		scene.rays.clear();
		scene.rays.push_back(Ray({ 100, 100 }, angle));
		scene.calculateAllRays();
		glUniform1i(glGetUniformLocation(program, "numberCircles"), scene.circles.size());
		for (int i = 0; i < scene.circles.size(); i++) {
			glUniform1f(glGetUniformLocation(program, ("circles[" + std::to_string(i) + "].x").c_str()), scene.circles[i].center.x);
			glUniform1f(glGetUniformLocation(program, ("circles[" + std::to_string(i) + "].y").c_str()), scene.circles[i].center.y);
			glUniform1f(glGetUniformLocation(program, ("circles[" + std::to_string(i) + "].radius").c_str()), scene.circles[i].radius);
		}
		glUniform1i(glGetUniformLocation(program, "numberRays"), scene.rays.size());
		for (int i = 0; i < scene.rays.size(); i++) {
			glUniform2f(glGetUniformLocation(program, ("rays[" + std::to_string(i) + "].start").c_str()), scene.rays[i].start.x, scene.rays[i].start.y);
			glUniform2f(glGetUniformLocation(program, ("rays[" + std::to_string(i) + "].end").c_str()), scene.rays[i].end.x, scene.rays[i].end.y);
			glUniform1f(glGetUniformLocation(program, ("rays[" + std::to_string(i) + "].angle").c_str()), scene.rays[i].angle);
		}

		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main(void)
{
	GLFWwindow *window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	std::string vertexShaderString = GetShadderFromSource(VERTEX_SHADER_FILENAME);
	std::string fragmentShaderString = GetShadderFromSource(FRAGMENT_SHADER_FILENAME);
	unsigned int program = CreateShader(vertexShaderString, fragmentShaderString);
	glUseProgram(program);
	runProgram(window, program);
	glDeleteProgram(program);
	glfwTerminate();
	return 0;
}
