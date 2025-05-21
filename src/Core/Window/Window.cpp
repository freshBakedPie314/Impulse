#include "Window.h"
#include <iostream>
#include <Maths.h>
#include <../Scene.h>
GLFWwindow* InitWindow()
{

	if (!glfwInit())
	{
		std::cerr << "GLFW Init Failed!\n";
		return nullptr;
	}

	//800, 600
	GLFWwindow* window = glfwCreateWindow(800, 800, "Impulse", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Window Creation Failed!\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Failed!\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return nullptr;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

	return window;
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	Scene* currentScene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
	if (currentScene == nullptr)
	{
		std::cout << "Scene pointer not set" << std::endl;
	}

	glViewport(0, 0, width, height);

	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	float desiredHeight = 10.0f;
	float desiredWidth = desiredHeight * aspectRatio;

	mat4 projection = projectionOrtho(-desiredWidth / 2.0f, desiredWidth / 2.0f,
		-desiredHeight / 2.0f, desiredHeight / 2.0f, 0.1f, 100.0f);

	currentScene->SetProjectionMat(projection);
}