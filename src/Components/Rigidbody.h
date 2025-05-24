#pragma once
#include <Components.h>
#include <Maths.h>

#define G -9.81f

class Rigidbody : public Component{
private:
public:
	bool m_UseGravity;
	float m_Velocity;
	float m_Acceleration;

	void PhysicsUpdate(Transform* transform , float deltaTime);
	
	Rigidbody() :
		Component("Rigidbody"),
		m_UseGravity(true),
		m_Velocity(0.0f),
		m_Acceleration(0.0f)
	{};
	~Rigidbody() = default;
};