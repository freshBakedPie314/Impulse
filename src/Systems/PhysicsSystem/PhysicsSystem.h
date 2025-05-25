#pragma once
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Scene.h>
#include <Components.h>

struct Projection {
	float min;
	float max;
};

class PhysicsSystem {
private:

public:
	void Update(Scene* scene , float deltaTime);
	vec3 AreColliding(const std::vector<vec3>& verticesA,
		const std::vector<vec3>& verticesB, const std::vector<vec3>& axes) const;
	Projection ProjectVertices(const std::vector<vec3>& vertices, const vec3& axis) const;
	bool IsOverlapping(const Projection& projA, const Projection& projB) const;
};