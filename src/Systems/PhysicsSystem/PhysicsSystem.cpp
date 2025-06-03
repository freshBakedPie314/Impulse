#include "PhysicsSystem.h"

void PhysicsSystem::Update(Scene* scenes, float deltaTime)
{
	std::vector<Entity*> entitiesWithColliders;

	// Update physics for all entities
	for (auto entity : scenes->GetEntities())
	{
		Rigidbody* rb = entity->GetComponent<Rigidbody>("Rigidbody");
		Transform* transform = entity->GetComponent<Transform>("Transform");
		Collider* collider = entity->GetComponent<Collider>("Collider");

		if (rb && transform)
		{
			rb->PhysicsUpdate(transform, deltaTime);
		}

		if (collider)
		{
			entitiesWithColliders.push_back(entity);
		}
	}

	//Detect and resolve collisions
	for (int i = 0; i < entitiesWithColliders.size(); i++)
	{
		for (int j = i + 1; j < entitiesWithColliders.size(); j++)
		{
			Entity* entityA = entitiesWithColliders[i];
			Entity* entityB = entitiesWithColliders[j];

			Collider* colliderA = entityA->GetComponent<Collider>("Collider");
			Collider* colliderB = entityB->GetComponent<Collider>("Collider");

			std::vector<vec3> axesA = colliderA->GetAxes();
			std::vector<vec3> axesB = colliderB->GetAxes();

			std::vector<vec3> worldVerticesA = colliderA->GetWorldVertices();
			std::vector<vec3> worldVerticesB = colliderB->GetWorldVertices();

			vec3 posA = entityA->GetComponent<Transform>("Transform")->GetPosition();
			vec3 posB = entityB->GetComponent<Transform>("Transform")->GetPosition();
			
			if (entityA->m_Shape == Shape::CIRCLE && entityB->m_Shape == Shape::CIRCLE)
			{
				vec3 posA = entityA->GetComponent<Transform>("Transform")->GetPosition();
				vec3 posB = entityB->GetComponent<Transform>("Transform")->GetPosition();

				float radius = 0.5f;

				float distance = (posB - posA).length();
				vec3 axis = normalize(posB - posA);

				if (distance <= 1.0f)
				{
					std::cout << "Collided\n";
				}

				worldVerticesA = { posA + (axis * radius), posA - (axis * radius) };
				worldVerticesB = { posB + (axis * radius), posB - (axis * radius) };

				axesA = { axis };
				axesB = {};
			}
			else if (entityA->m_Shape == Shape::CIRCLE)
			{
				vec3 posA = entityA->GetComponent<Transform>("Transform")->GetPosition();
				float radius = 0.5f;

				vec3 closestPoint = ClosestPointInPolygon(worldVerticesB, posA);
				vec3 additionalAxis = closestPoint - posA;
				additionalAxis = normalize(additionalAxis);

				axesA = {};
				axesB.push_back(additionalAxis);
			}
			else if (entityB->m_Shape == Shape::CIRCLE)
			{
				vec3 posB = entityB->GetComponent<Transform>("Transform")->GetPosition();
				float radius = 0.5f;

				vec3 closestPoint = ClosestPointInPolygon(worldVerticesA, posB);
				vec3 additionalAxis = closestPoint - posB;
				additionalAxis = normalize(additionalAxis);

				axesB = {};
				axesA.push_back(additionalAxis);
			}
			else
			{
				;
			}

			CollisionInfo collisionInfo = GetMTV(worldVerticesA, worldVerticesB, axesA, axesB);

			if (collisionInfo.penetration > 0.0f) // Collision detected
			{
				collisionInfo.entityA = entityA;
				collisionInfo.entityB = entityB;

				ResolveCollision(collisionInfo);
			}
			
		}

	}
}

vec3 PhysicsSystem::ClosestPointInLineSegment(const vec3& a, const vec3& b, const vec3& point)
{
	vec3 segment = b - a;
	vec3 toPoint = point - a;

	float t = dot(toPoint, segment) / segment.sqMagnitude();
	t = std::clamp(t, 0.0f, 1.0f);

	return a + segment * t;
}

vec3 PhysicsSystem::ClosestPointInPolygon(const std::vector<vec3>& vertices, const vec3& point)
{
	if (vertices.empty()) return vec3(0, 0, 0);

	float closestDistSq = (point - vertices[0]).sqMagnitude();
	vec3 closestPoint = vertices[0];

	for (size_t i = 0; i < vertices.size(); i++)
	{
		const vec3& a = vertices[i];
		const vec3& b = vertices[(i + 1) % vertices.size()];

		vec3 pointOnSegment = ClosestPointInLineSegment(a, b, point);
		float distSq = (pointOnSegment - point).sqMagnitude();

		if (distSq < closestDistSq)
		{
			closestDistSq = distSq;
			closestPoint = pointOnSegment;
		}

		float vertexDistSq = (a - point).sqMagnitude();
		if (vertexDistSq < closestDistSq)
		{
			closestDistSq = vertexDistSq;
			closestPoint = a;
		}
	}

	return closestPoint;
}

CollisionInfo PhysicsSystem::GetMTV(const std::vector<vec3>& verticesA,
									const std::vector<vec3>& verticesB,
									const std::vector<vec3>& axesA,
									const std::vector<vec3>& axesB,
									const Entity* circle) const
{
	CollisionInfo info;
	float minOverlap = FLT_MAX;
	vec3 mtvAxis;

	// Combine all axes to check
	std::vector<vec3> allAxes = axesA;
	allAxes.insert(allAxes.end(), axesB.begin(), axesB.end());

	for (const auto& axis : allAxes)
	{
		if (axis.length() < 0.001f) continue;

		vec3 normalizedAxis = normalize(axis);

		Projection projA = ProjectVertices(verticesA, normalizedAxis , circle);
		Projection projB = ProjectVertices(verticesB, normalizedAxis, circle);

		if (!IsOverlapping(projA, projB))
		{
			// No collision
			info.penetration = 0.0f;
			return info;
		}

		// Calculate overlap
		float overlap = std::min(projA.max, projB.max) - std::max(projA.min, projB.min);

		if (overlap < minOverlap)
		{
			minOverlap = overlap;
			mtvAxis = normalizedAxis;
		}
	}

	// Ensure MTV points from A to B
	vec3 centerA = GetCentroid(verticesA);
	vec3 centerB = GetCentroid(verticesB);
	vec3 direction = centerB - centerA;

	if (dot(mtvAxis, direction) < 0)
	{
		mtvAxis = mtvAxis * -1.0f;
	}

	info.mtv = mtvAxis * minOverlap;
	info.penetration = minOverlap;
	return info;
}

Projection PhysicsSystem::ProjectVertices(const std::vector<vec3>& vertices, const vec3& axis, const Entity* circle) const
{
	if (vertices.empty())
	{
		vec3 circleCenter = circle->GetComponent<Transform>("Transform")->GetPosition();
		float circleRadius = 0.5f;
		// Handle circle case
		if (axis.length() > 0.001f)
		{
			vec3 normalizedAxis = normalize(axis);
			float projection = dot(circleCenter, normalizedAxis);
			return { projection - circleRadius, projection + circleRadius };
		}
		return { 0.0f, 0.0f };
	}

	//Point
	if (axis.x == 0.0f && axis.y == 0.0f)
	{
		return { -FLT_MAX, FLT_MAX };
	}

	Projection proj; //Projection is the min and max values of vertices projected (dot product) on axis

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

vec3 PhysicsSystem::GetCentroid(const std::vector<vec3>& vertices) const
{
	if (vertices.empty()) return vec3(0.0f, 0.0f, 0.0f);

	vec3 centroid(0.0f, 0.0f, 0.0f);
	for (const auto& vertex : vertices)
	{
		centroid += vertex;
	}
	return centroid / static_cast<float>(vertices.size());
}

void PhysicsSystem::ResolveCollision(const CollisionInfo& collision)
{
	Rigidbody* rbA = collision.entityA->GetComponent<Rigidbody>("Rigidbody");
	Rigidbody* rbB = collision.entityB->GetComponent<Rigidbody>("Rigidbody");
	Transform* transformA = collision.entityA->GetComponent<Transform>("Transform");
	Transform* transformB = collision.entityB->GetComponent<Transform>("Transform");

	vec3 separation = collision.mtv * 0.5f; // Split separation between both objects

	if (rbA && rbB) 
	{
		vec3 newPosA = transformA->GetPosition() - separation;
		vec3 newPosB = transformB->GetPosition() + separation;

		transformA->SetPosition(newPosA);
		transformB->SetPosition(newPosB);

		vec3 lineOfAction = normalize(collision.mtv); // In convex shapes MTV is the line of action

		vec3 uA = rbA->m_Velocity;
		vec3 uB = rbB->m_Velocity;

		float mA = rbA->m_Mass;
		float mB = rbB->m_Mass;

		// Project velocities onto the line of action, velocity componet along line of Action
		float uA_ = dot(uA, lineOfAction);
		float uB_ = dot(uB, lineOfAction);

		// 1D elastic collision along line of Action
		float vA = (uA_ * (mA - mB) + 2.0f * mB * uB_) / (mA + mB);
		float vB = (uB_ * (mB - mA) + 2.0f * mA * uA_) / (mA + mB);

		// Change in line of action component
		float deltaVA = vA - uA_;
		float deltaVB = vB - uB_;

		// Apply changes along the normal, dont disturb the normal velocity components
		rbA->m_Velocity += lineOfAction * deltaVA;
		rbB->m_Velocity += lineOfAction * deltaVB;
	}
	else
	{
		std::cout << "No Rigidbody attached to the entity with collider" << std::endl;
	}
}