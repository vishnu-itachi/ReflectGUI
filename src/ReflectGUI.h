#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "ReflectRNG/Scene.h"

class ReflectGUI
{
public:
	int screenWidth, screenHeight;
	std::string vertexShaderFileName, fragmentShaderFileName;
	GLFWwindow *window;
	unsigned int program;

	ReflectGUI(int screenWidth, int screenHeight, std::string vertexShaderFileName, std::string fragmentShaderFileName, int &initialised);
	~ReflectGUI();
	void runProgramLoop(Scene scene);

private:
	static std::string GetShadderFromSource(const std::string &filepath);
	static unsigned int CompileShader(unsigned int type, const std::string &source);
	static bool CheckForError(unsigned int program, int whatToCheck);
	static unsigned int CreateShader(const std::string &vertexshader, const std::string &fragmentshader);
	int prepareProgramAndWindow();
};
