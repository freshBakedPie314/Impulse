#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Scene.h>
#include <Components.h>

class PhysicsSystem {
private:

public:
	void Update(Scene* scene , float deltaTime);
};