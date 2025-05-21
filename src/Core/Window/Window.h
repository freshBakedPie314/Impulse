#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* InitWindow();
void WindowResizeCallback(GLFWwindow* wimdow, int width, int height);