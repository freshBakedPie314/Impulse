#include "RendererSystem.h"

GLFWwindow* InitWindow() 
{

	if (!glfwInit()) 
	{
		std::cerr << "GLFW Init Failed!\n";
		return nullptr;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "Impulse", nullptr, nullptr);
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

	return window;
}

void RendererSystem::Update(Scene* scene)
{
	for (auto a : scene->GetEntities())
	{
		a->GetVBO()->Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}
