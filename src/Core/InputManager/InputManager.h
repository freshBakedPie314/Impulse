#pragma once
#include <Scene.h>

enum struct MouseState
{
	LEFT_PRESSED,
	RIGHT_PRESSED,
	NONE
};

enum struct SimulationState
{
	PAUSED,
	PLAYED
};

class InputManager {
private:

	Scene* m_CurrentScene;
	MouseState m_MouseButtonState;
	SimulationState m_SimulationState;
	double m_LastMouseX;
	double m_LastMouseY;
	float m_CameraSpeed;
	float m_deltaTime;

public:

	InputManager(Scene* scene)
		: m_CurrentScene(scene),
		m_MouseButtonState(MouseState::NONE),
		m_SimulationState(SimulationState::PAUSED),
		m_LastMouseX(0.0),
		m_LastMouseY(0.0),
		m_CameraSpeed(10.0f),
		m_deltaTime(0.0f) {}
	~InputManager() = default;

	static void WindowResizeCallback(GLFWwindow* wimdow, int width, int height);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MousePositionChangeCallback(GLFWwindow* window, double xpos, double ypos);
	static void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void hanldeWindowResize(GLFWwindow* window, int width, int height);
	void hanldeMouseButtonPress(GLFWwindow* window, int button, int action, int mods);
	void hanldeMousePositionChange(GLFWwindow* window, double xpos, double ypos);
	void hanldeKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);

	inline void SetCameraSensitivity(float sensitivity) { m_CameraSpeed = sensitivity; }
	inline SimulationState GetSimulationState() const { return m_SimulationState; }
	inline void SetDeltaTime(float deltaTime) { m_deltaTime = deltaTime; }
};