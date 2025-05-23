#include "RendererSystem.h"
#include "Scene.h"
#include <filesystem>
#include <Window.h>
#include "../Components/Transform.h"
int main() 
{
	std::cout << "Version: Alpha 0.1" << std::endl;
	
	GLFWwindow* window = InitWindow();

	int initialWidth, initialHeight;
	glfwGetFramebufferSize(window, &initialWidth, &initialHeight);
	
	Scene* currentScene = new Scene();
	glfwSetWindowUserPointer(window, currentScene);

	//Set a custom pointer to current scene, useful while setting projection matrix
	WindowResizeCallback(window, initialWidth, initialHeight); 

	Entity* a = new Entity(Shape::CIRCLE);
	currentScene->AddEntity(a);
	a->GetShader()->SetUniform4f("u_color", 0.898f, 0.239f, 0.0f, 1.0f);

	RendererSystem* rendererSystem = new RendererSystem();

	a->AddComponent<Transform>("Transform", vec3{0.0f, 1.0f, 0.0f}, vec3{0.0 , 0.0, 0.1f}, vec3{1.0f , 1.0f ,1.0f});
	//mat4 model = createTranformationMatrix(vec3{ 0.0f , 0.0f, 0.0f }, 0.0f);
	
	Entity* b = new Entity(Shape::CIRCLE);
	currentScene->AddEntity(b);
	b->GetShader()->SetUniform4f("u_color", 0.898f, 0.239f, 0.0f, 1.0f);
	b->AddComponent<Transform>("Transform", vec3{ 2.0f, -1.0f, 0.0f }, vec3{ 0.0 , 0.0, 0.1f }, vec3{ 1.0f , 1.0f ,1.0f });
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
