#include "RendererSystem.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void InitWindow() {
	if (!glfwInit()) {
		std::cerr << "GLFW Init Failed!\n";
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "PhysicsEngine", nullptr, nullptr);
	if (!window) {
		std::cerr << "Window Creation Failed!\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW Init Failed!\n";
		return;
	}

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}
