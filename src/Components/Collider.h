#pragma once
#include <Components.h>
#include <Maths.h>

class Collider : public Component{
private:

public:
	Collider();
	~Collider() = default;

	std::vector<vec3> GetWorldVertices() const;
	void PhysicsUpdate(float deltaTime);
	std::vector<vec3> Collider::GetAxes();
};