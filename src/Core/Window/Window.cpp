#include "Window.h"


GLFWwindow* InitWindow(InputManager* inputManager)
{
	// Initiliase GLFW
	if (!glfwInit())
	{
		std::cerr << "GLFW Init Failed!\n";
		return nullptr;
	}

	//Make Window and set as context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Impulse", nullptr, nullptr);
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

	glfwSetWindowUserPointer(window, inputManager);

	int initialWidth, initialHeight;
	glfwGetFramebufferSize(window, &initialWidth, &initialHeight);

	inputManager->WindowResizeCallback(window, initialWidth, initialHeight);

	//------------Register Callbacks-------------
	glfwSetFramebufferSizeCallback(window, InputManager::WindowResizeCallback);
	glfwSetMouseButtonCallback(window, InputManager::MouseButtonCallback);
	glfwSetCursorPosCallback(window, InputManager::MousePositionChangeCallback);
	glfwSetKeyCallback(window, InputManager::KeyPressedCallback);
	return window;
}
