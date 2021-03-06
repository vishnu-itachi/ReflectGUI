#include "ReflectGUI.h"
#include "ReflectRNG/Scene.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

ReflectGUI::ReflectGUI(int screenWidth, int screenHeight, std::string vertexShaderFileName, std::string fragmentShaderFileName, int &initialised)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->vertexShaderFileName = vertexShaderFileName;
	this->fragmentShaderFileName = fragmentShaderFileName;

	initialised = prepareProgramAndWindow();
}

ReflectGUI::~ReflectGUI()
{
	glDeleteProgram(this->program);
	glfwTerminate();
}

std::string ReflectGUI::GetShadderFromSource(const std::string &filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss;
	while (getline(stream, line)) ss << line << "\n";
	return ss.str();
}

unsigned int ReflectGUI::CompileShader(unsigned int type, const std::string &source)
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

bool ReflectGUI::CheckForError(unsigned int program, int whatToCheck)
{
	int result;
	glGetProgramiv(program, whatToCheck, &result);
	if (result) return false;

	int length;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	auto message = (char *) alloca(length * sizeof(char));
	glGetProgramInfoLog(program, length, &length, message);

	std::cout << "Failed to link" << std::endl;
	std::cout << message << std::endl;
	return true;
}

unsigned int ReflectGUI::CreateShader(const std::string &vertexshader, const std::string &fragmentshader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	if (CheckForError(program, GL_LINK_STATUS)) return 0;
	glValidateProgram(program);
	if (CheckForError(program, GL_VALIDATE_STATUS)) return 0;
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void ReflectGUI::runProgramLoop(Scene scene)
{
	while (!glfwWindowShouldClose(this->window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		scene.drawScene(this->window, this->program, this->screenWidth, this->screenHeight);
		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}
}

int ReflectGUI::prepareProgramAndWindow()
{
	if (!glfwInit())
		return -1;

	this->window = glfwCreateWindow(this->screenWidth, this->screenHeight, "Hello World", nullptr, nullptr);
	if (!this->window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	std::string vertexShaderString = GetShadderFromSource(vertexShaderFileName);
	std::string fragmentShaderString = GetShadderFromSource(fragmentShaderFileName);
	this->program = CreateShader(vertexShaderString, fragmentShaderString);
	glUseProgram(this->program);
	return 0;
}
