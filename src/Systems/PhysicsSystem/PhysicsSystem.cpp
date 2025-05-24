#include "PhysicsSystem.h"

void PhysicsSystem::Update(Scene* scenes, float deltaTime)
{
	for (auto entity : scenes->GetEntities())
	{
		for (auto component : entity->GetComponents())
		{
			if (component.first == "Rigidbody")
			{
				Rigidbody* rb = dynamic_cast<Rigidbody*>(component.second);
				rb->PhysicsUpdate(entity->GetComponent<Transform>("Transform") , deltaTime);
			}
		}
	}
}