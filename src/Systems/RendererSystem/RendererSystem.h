#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Core/Scene.h"

GLFWwindow* InitWindow();

class RendererSystem
{
private:

public:
	void Update(Scene* scene);
};