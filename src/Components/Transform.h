#pragma once
#include <Entity.h>
#include <Components.h>
#include <vector>
#include <Maths.h>

class Transform : public Component{
public:
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
	std::vector<std::vector<float>> m_WorldVertexPositions;
	mat4 m_model;
	Transform(const std::string& name, 
		vec3 postion = {0.0f , 0.0f ,0.f }, 
		vec3 rotation = { 0.0f , 0.0f ,0.f }, 
		vec3 scale = { 1.0f , 1.0f ,1.f });

	Transform(vec3 position = { 0.0f , 0.0f ,0.f },
		vec3 rotation = { 0.0f , 0.0f ,0.f },
		vec3 scale = { 1.0f , 1.0f ,1.f });

	void SetPosition(const vec3& newPos) {
		m_Position = newPos;
		RecomputeModelMatrix();
	}

	void SetRotation(const vec3& newRot) {
		m_Rotation = newRot;
		RecomputeModelMatrix();
	}

	void SetScale(const vec3& newScale) {
		m_Scale = newScale;
		RecomputeModelMatrix();
	}

	vec3& GetPosition() { return m_Position; }
	const mat4& GetModelMatrix() const { return m_model; }
	void OnAddedToEntity(Entity* owner) override;
	void PhysicsUpdate(float deltaTime);
private:
	void RecomputeModelMatrix() {
		m_model = createTranformationMatrix(m_Position, m_Rotation.z);
	}
};