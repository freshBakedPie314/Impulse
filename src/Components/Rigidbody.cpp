#include "Rigidbody.h"

void Rigidbody::PhysicsUpdate(Transform* transform, float deltaTime)
{
	if (m_UseGravity)
	{
		m_Velocity += G * deltaTime;
		vec3 pos = transform->m_Position;
		pos.y += m_Velocity * deltaTime;
		transform->m_Position = pos;
	}
}