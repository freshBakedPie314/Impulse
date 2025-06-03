#pragma once
#include <Components.h>
#include <Maths.h>

#define G -9.81f

class Rigidbody : public Component{
private:
public:
	bool m_UseGravity;
	vec3 m_Velocity;
	vec3 m_Acceleration;
	float m_Mass;
	bool m_IsStatic;
	Rigidbody() :
		Component("Rigidbody"),
		m_UseGravity(true),
		m_Velocity({ 0.0f, 0.0f, 0.0f }),
		m_Acceleration({ 0.0f, 0.0f, 0.0f }),
		m_Mass(1.0f),
		m_IsStatic(false)
	{};
	void PhysicsUpdate(Transform* transform , float deltaTime);
	~Rigidbody() = default;
	void AddForce(vec3 dir, float mag);
	void AddImpulse(vec3 dir, float mag);
	void ResolveCollision();
};