#include "RendererSystem.h"
#include "Scene.h"
#include <filesystem>
#include <Window.h>

int main() 
{
	std::cout << "Version: Alpha 0.1" << std::endl;
	
	GLFWwindow* window = InitWindow();
	std::cout << "Initialized Window" << std::endl;
	std::cout << "STATUS: OK" << std::endl;
	int initialWidth, initialHeight;
	glfwGetFramebufferSize(window, &initialWidth, &initialHeight);
	
	Scene* currentScene = new Scene();
	glfwSetWindowUserPointer(window, currentScene);

	//Set a custom pointer to current scene, useful while setting projection matrix
	WindowResizeCallback(window, initialWidth, initialHeight); 

	Entity* a = new Entity(Shape::CIRCLE);
	currentScene->AddEntity(a);

	RendererSystem* rendererSystem = new RendererSystem();

	a->GetShader()->SetUniform4f("u_color", 0.898f, 0.239f, 0.0f, 1.0f);

	vec3 transformation = { 1.0f , 0.0f , 0.0f };
	mat4 model = createTranformationMatrix(transformation, 0.0f);
	a->GetShader()->SetUniform4mat("u_model", model);

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
