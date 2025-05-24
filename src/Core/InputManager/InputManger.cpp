#include "InputManager.h"

//------------------ Call back functions ----------------//
void InputManager::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (manager) manager->hanldeWindowResize(window, width, height);
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (manager) manager->hanldeMouseButtonPress(window, button, action, mods);
}

void InputManager::MousePositionChangeCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (manager) manager->hanldeMousePositionChange(window, xpos, ypos);
}

void InputManager::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	InputManager* manager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (manager) manager->hanldeKeyPressed(window, key, scancode, action, mods);
}

//----------- Non - static fucntions ---------------//
void InputManager::hanldeWindowResize(GLFWwindow* window, int width, int height)
{
	if (m_CurrentScene == nullptr)
	{
		std::cout << "Scene pointer not set" << std::endl;
	}

	glViewport(0, 0, width, height);

	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	float desiredHeight = 10.0f;
	float desiredWidth = desiredHeight * aspectRatio;

	mat4 projection = projectionOrtho(-desiredWidth / 2.0f, desiredWidth / 2.0f,
		-desiredHeight / 2.0f, desiredHeight / 2.0f, 0.1f, 100.0f);

	m_CurrentScene->SetProjectionMat(projection);
}

void InputManager::hanldeMouseButtonPress(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &m_LastMouseX, &m_LastMouseY);
		m_MouseButtonState = MouseState::LEFT_PRESSED;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		m_MouseButtonState = MouseState::NONE;
	}
}

void InputManager::hanldeMousePositionChange(GLFWwindow* window, double xpos, double ypos)
{
	if (m_MouseButtonState == MouseState::LEFT_PRESSED)
	{
		double deltaX = xpos - m_LastMouseX;
		double deltaY = ypos - m_LastMouseY;

		m_LastMouseX = xpos;
		m_LastMouseY = ypos;

		if (m_CurrentScene == nullptr)
		{
			return;
		}
		vec3 cameraPos = m_CurrentScene->GetCameraPos();
		cameraPos.x -= deltaX * m_CameraSpeed * m_deltaTime;
		cameraPos.y += deltaY * m_CameraSpeed * m_deltaTime;
		m_CurrentScene->SetViewMat(cameraPos);
	}
}

void InputManager::hanldeKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		if (m_SimulationState == SimulationState::PAUSED) m_SimulationState = SimulationState::PLAYED;
		else m_SimulationState = SimulationState::PAUSED;
	}
}