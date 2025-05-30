#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Scene.h>
#include <Components.h>

class RendererSystem
{
private:
	Scene* m_CurrentScene;
public:
	void Update(Scene* scene);
};