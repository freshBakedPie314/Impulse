#include "PhysicsSystem.h"

void PhysicsSystem::Update(Scene* scenes, float deltaTime)
{
	std::vector<Entity*> entitiesWithColliders;
	for (auto entity : scenes->GetEntities())
	{
		Rigidbody* rb = dynamic_cast<Rigidbody*>(entity->GetComponent<Rigidbody>("Rigidbody"));
		Transform* transform = dynamic_cast<Transform*>(entity->GetComponent<Transform>("Transform"));
		Collider* collider = dynamic_cast<Collider*>(entity->GetComponent<Collider>("Collider"));
		if (rb && transform)
		{
			rb->PhysicsUpdate(transform, deltaTime);
		}

		if (collider)
		{
			entitiesWithColliders.push_back(entity);
		}
	}

	for (int i = 0; i < entitiesWithColliders.size(); i++)
	{
		for (int j = i + 1; j < entitiesWithColliders.size(); j++)
		{
			//Make Pairs and get their axes
			Entity* entityA = entitiesWithColliders[i];
			Entity* entityB = entitiesWithColliders[j];

			Collider* colliderA = entityA->GetComponent<Collider>("Collider");
			Collider* colliderB = entityB->GetComponent<Collider>("Collider");

			Rigidbody* rbA = entityA->GetComponent<Rigidbody>("Rigidbody");
			Rigidbody* rbB = entityB->GetComponent<Rigidbody>("Rigidbody");

			//For each axes
			std::vector<vec3> axesA = colliderA->GetAxes();
			std::vector<vec3> axesB = colliderB->GetAxes();

			std::vector<vec3> worldVerticesA = colliderA->GetWorldVertices();
			std::vector<vec3> worldVerticesB = colliderB->GetWorldVertices();

			vec3 separatedA = AreColliding(worldVerticesA, worldVerticesB, axesA);
			vec3 separatedB = AreColliding(worldVerticesA, worldVerticesB, axesB);
			if (separatedA == vec3{0.0f, 0.0f, 0.0f} || separatedB == vec3{0.0f, 0.0f, 0.0f})
			{
				;
			}
			else
			{
				rbA->ResolveCollision();
				rbB->ResolveCollision();

				if (separatedA < separatedB)
				{
					float mag = separatedA.magnitude();
					rbA->AddImpulse(normalize(separatedA), mag);
					rbB->AddImpulse(normalize(separatedA) * -1.0f, mag);
					std::cout << mag << std::endl;
				}
				else
				{
					float mag = separatedB.magnitude();
					rbB->AddImpulse(normalize(separatedB), mag);
					rbA->AddImpulse(normalize(separatedB) * -1.0f, mag);
					std::cout << mag << std::endl;

				}
			}
		}
	}
}

vec3 PhysicsSystem::AreColliding(const std::vector<vec3>& verticesA, const std::vector<vec3>& verticesB,
	const std::vector<vec3>& axes) const 
{
	float minOverlap;
	vec3 minOverlapAxis;
	bool isOverlapping = false;
	for (const auto& axis : axes) 
	{
		Projection projA = ProjectVertices(verticesA, axis);
		Projection projB = ProjectVertices(verticesB, axis);
		
		if (!IsOverlapping(projA, projB))
		{
			return vec3(); // Found a separating axis, polygons are not colliding
		}
		else
		{
			float overlap = std::min(projA.max, projB.max) - std::max(projA.min, projB.min);
			if (!isOverlapping || overlap < minOverlap)
			{
				minOverlap = overlap;
				minOverlapAxis = axis;
				isOverlapping = true;
			}
		}
	}
	return minOverlapAxis * minOverlap; // No separating axis found among these axes
}

Projection PhysicsSystem::ProjectVertices(const std::vector<vec3>& vertices, const vec3& axis) const
{
	if (vertices.empty())
	{
		std::cout << "Empty vertices" << std::endl;
		return { 0.0f , 0.0f };
	}

	if (axis.x == 0.0f && axis.y == 0.0f)
	{
		return { -FLT_MAX, FLT_MAX };
	}

	Projection proj;

	proj.min = dot(vertices[0], axis);
	proj.max = dot(vertices[0], axis);

	for (const auto& vertex : vertices)
	{
		float dotP = dot(vertex, axis);
		proj.min = std::min(dotP, proj.min);
		proj.max = std::max(dotP, proj.max);
	}
	return proj;
}

bool PhysicsSystem::IsOverlapping(const Projection& projA, const Projection& projB) const
{
	return (projA.max >= projB.min && projB.max >= projA.min);
}
