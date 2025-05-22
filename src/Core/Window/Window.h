#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* InitWindow();
void WindowResizeCallback(GLFWwindow* wimdow, int width, int height);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void MousePositionChangeCallback(GLFWwindow* window, double xpos, double ypos);