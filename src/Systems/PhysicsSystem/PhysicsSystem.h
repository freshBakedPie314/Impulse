#pragma once
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Scene.h>
#include <Components.h>

struct Projection {
	float min;
	float max;
};

struct CollisionInfo {
	Entity* entityA;
	Entity* entityB;
	vec3 mtv;
	float penetration;
};

class PhysicsSystem {
private:

public:
	void Update(Scene* scene , float deltaTime);
	vec3 AreColliding(const std::vector<vec3>& verticesA, 
						const std::vector<vec3>& verticesB, 
						const std::vector<vec3>& axes) const;
	
	CollisionInfo GetMTV(const std::vector<vec3>& verticesA,
		const std::vector<vec3>& verticesB,
		const std::vector<vec3>& axesA,
		const std::vector<vec3>& axesB,
		const Entity* circle = nullptr) const;

	vec3 ClosestPointInLineSegment(const vec3& a, const vec3& b, const vec3& point);
	vec3 ClosestPointInPolygon(const std::vector<vec3>& vertices, const vec3& point);
	void ResolveCollision(const CollisionInfo& collision);
	vec3 GetCentroid(const std::vector<vec3>& vertices) const;
	Projection ProjectVertices(const std::vector<vec3>& vertices, const vec3& axis, const Entity* circle = nullptr) const;
	bool IsOverlapping(const Projection& projA, const Projection& projB) const;
};