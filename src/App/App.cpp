#include "RendererSystem.h"
#include "Scene.h"
#include <filesystem>
int main() 
{
	GLFWwindow* window = InitWindow();
	
	Scene* currentScene = new Scene();

	Entity* a = new Entity(Shape::CIRCLE);
	currentScene->AddEntity(a);
	RendererSystem* rendererSystem = new RendererSystem();
	a->GetShader()->SetUniform4f("u_color", 0.898f, 0.239f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.145f, 0.141f, 0.133f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rendererSystem->Update(currentScene);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
