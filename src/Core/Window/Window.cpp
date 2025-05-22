#include "Window.h"
#include <iostream>
#include <Maths.h>
#include <../Scene.h>

enum struct MouseState
{
	LEFT_PRESSED,
	RIGHT_PRESSED,
	NONE
};

MouseState* currentMouseState = new MouseState(MouseState::NONE);
double initalXPos, intialYPos;
GLFWwindow* InitWindow()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW Init Failed!\n";
		return nullptr;
	}

	//800, 600
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Impulse", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Window Creation Failed!\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwGetCursorPos(window, &initalXPos, &intialYPos);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Failed!\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return nullptr;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Window Resize Callback
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

	//Mouse Click/Release Callback
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	//Mouse Position Callback
	glfwSetCursorPosCallback(window, MousePositionChangeCallback);	
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

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "Pressed\n";
		glfwGetCursorPos(window, &initalXPos, &intialYPos);
		*currentMouseState = MouseState::LEFT_PRESSED;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		*currentMouseState = MouseState::NONE;
	}
}

void MousePositionChangeCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (*currentMouseState == MouseState::LEFT_PRESSED)
	{
		double deltaX = xpos - initalXPos;
		double deltaY = ypos - intialYPos;

		initalXPos = xpos;
		intialYPos = ypos;

		float cameraSpeed = 0.01f;

		Scene* currentScene = static_cast<Scene*>(glfwGetWindowUserPointer(window));
		if (currentScene == nullptr)
		{
			return;
		}
		vec3 cameraPos = currentScene->GetCameraPos();
		cameraPos.x -= deltaX * cameraSpeed;
		cameraPos.y += deltaY * cameraSpeed;
		currentScene->SetViewMat(cameraPos);
	}
}