#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Core/Scene.h"

class RendererSystem
{
private:
	Scene* m_CurrentScene;
public:
	void Update(Scene* scene);
};