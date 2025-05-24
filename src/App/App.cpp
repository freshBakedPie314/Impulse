#include <filesystem>
#include <memory>

#include <RendererSystem.h>
#include <PhysicsSystem.h>
#include <Window.h>
#include <Components.h>


int main() 
{
	std::cout << "Version: Alpha 0.1" << std::endl;
	
	std::unique_ptr<Scene> currentScene = std::make_unique<Scene>();
	std::unique_ptr<InputManager> inputManager = std::make_unique<InputManager>(currentScene.get());
	GLFWwindow* window = InitWindow(inputManager.get());
	
	std::unique_ptr<RendererSystem> rendererSystem = std::make_unique<RendererSystem>();
	std::unique_ptr<PhysicsSystem> physicsSystem = std::make_unique<PhysicsSystem>();

	
	std::unique_ptr <Entity> a = std::make_unique<Entity>(Shape::CIRCLE);	
	a->GetShader()->SetUniform4f("u_color", 0.898f, 0.239f, 0.0f, 1.0f);
	a->AddComponent<Transform>("Transform", vec3{0.0f, 3.0f, 0.0f}, vec3{0.0 , 0.0, 0.1f}, vec3{1.0f , 1.0f ,1.0f});
	a->AddComponent<Rigidbody>("Rigidbody");
	currentScene->AddEntity("A", std::move(a));

	std::unique_ptr <Entity> b = std::make_unique<Entity>(Shape::CIRCLE);
	b->GetShader()->SetUniform4f("u_color", 0.898f, 0.239f, 0.0f, 1.0f);
	b->AddComponent<Transform>("Transform", vec3{ 2.0f, 2.0f, 0.0f }, vec3{ 0.0 , 0.0, 0.1f }, vec3{ 1.0f , 1.0f ,1.0f });
	b->AddComponent<Rigidbody>("Rigidbody");
	currentScene->AddEntity("B", std::move(b));

	float lastFrameTime = 0.0f;
	float deltaTime = 0.0f;
	while (!glfwWindowShouldClose(window)) 
	{

		// --- Calculate Delta Time ---
		float currentFrameTime = static_cast<float>(glfwGetTime()); 
		deltaTime = currentFrameTime - lastFrameTime;               
		lastFrameTime = currentFrameTime;
		inputManager->SetDeltaTime(deltaTime);
		// --------------------------

		glClearColor(0.145f, 0.141f, 0.133f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rendererSystem->Update(currentScene.get());
		if(inputManager->GetSimulationState() == SimulationState::PLAYED) 
			physicsSystem->Update(currentScene.get(), deltaTime);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
