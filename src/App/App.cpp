#include "RendererSystem.h"
#include "Scene.h"

int main() 
{
	GLFWwindow* window = InitWindow();
	
	Scene* currentScene = new Scene();
	Entity* a = new Entity;
	currentScene->AddEntity(a);
	RendererSystem* rendererSystem = new RendererSystem();

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
