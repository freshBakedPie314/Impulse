#include "Transform.h"

//Unused
Transform::Transform(const std::string& name, vec3 postion, vec3 rotation, vec3 scale)
	:Component(name),
	m_Position(postion),
	m_Rotation(rotation),
	m_Scale(scale)
{
	m_model = createTranformationMatrix(m_Position, m_Rotation.z);
}

Transform::Transform(vec3 position, vec3 rotation, vec3 scale)
	: Component("Transform"),
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(scale)
{
	m_model = createTranformationMatrix(m_Position, m_Rotation.z);
}

void Transform::OnAddedToEntity(Entity* owner)
{
	m_Owner = owner;
}
void Transform::PhysicsUpdate(float deltaTime)
{

}