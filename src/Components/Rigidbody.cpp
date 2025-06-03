#include "Rigidbody.h"

void Rigidbody::PhysicsUpdate(Transform* transform, float deltaTime)
{
    if (m_IsStatic) return;

	if (m_UseGravity)
	{
        m_Acceleration.y += G;
	}

    m_Velocity += m_Acceleration * deltaTime;

    vec3 currentPos = transform->GetPosition();
    vec3 newPos = currentPos + m_Velocity * deltaTime;
    transform->SetPosition(newPos);
    
    m_Acceleration = { 0.0f, 0.0f, 0.0f };
}

void Rigidbody::AddForce(vec3 dir , float mag)
{
    dir = normalize(dir);
    m_Acceleration += dir * mag;
}

void Rigidbody::AddImpulse(vec3 dir, float mag)
{
    dir = normalize(dir);
    m_Velocity = { 0.0f , 0.f , 0.f };
    m_Acceleration = dir * mag;
}

void Rigidbody::ResolveCollision()
{
    m_Velocity = { 0.0f , 0.f , 0.f };
    m_Acceleration = { 0.0f , 0.f , 0.f };
}
