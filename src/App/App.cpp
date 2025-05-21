#include "RendererSystem.h"
#include "Scene.h"
#include <filesystem>

mat4 projection;

void WindowResizeCallback(GLFWwindow* wimdow, int width, int height)
{
	std::cout << width << ' ' << height << std::endl;
	glViewport(0, 0, width, height);

	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	float desiredHeight = 10.0f;
	float desiredWidth = desiredHeight * aspectRatio;

	projection = projectionOrtho(-desiredWidth / 2.0f, desiredWidth / 2.0f,
		-desiredHeight / 2.0f, desiredHeight / 2.0f, 0.1f, 100.0f);
	
}

int main() 
{
	GLFWwindow* window = InitWindow();
	glfwSetFramebufferSizeCallback(window, WindowResizeCallback);

	int initialWidth, initialHeight;
	glfwGetFramebufferSize(window, &initialWidth, &initialHeight);
	WindowResizeCallback(window, initialWidth, initialHeight);

	Scene* currentScene = new Scene();

	Entity* a = new Entity(Shape::CIRCLE);
	currentScene->AddEntity(a);
	RendererSystem* rendererSystem = new RendererSystem();
	a->GetShader()->SetUniform4f("u_color", 0.898f, 0.239f, 0.0f, 1.0f);

	vec3 transformation = { 1.0f , 0.0f , 0.0f };
	vec3 camera = { 0.5f , 0.0f , 1.0f };
	vec3 to = camera;
	to.z -= 1.0f;
	mat4 view = lookAt(camera , to);
	a->GetShader()->SetUniform4mat("u_view", view);
	mat4 model = createTranformationMatrix(transformation, 0.0f);
	a->GetShader()->SetUniform4mat("u_model", model);

	projection = projectionOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
	a->GetShader()->SetUniform4mat("u_projection", projection);
	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.145f, 0.141f, 0.133f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		a->GetShader()->SetUniform4mat("u_projection", projection);
		rendererSystem->Update(currentScene);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
