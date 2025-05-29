#include "Collider.h"

Collider::Collider() : Component("Collider")
{

}

std::vector<vec3> Collider::GetWorldVertices() const 
{
    std::vector<vec3> worldVertices;
    if (!m_Owner) return worldVertices;

    Transform* transform = m_Owner->GetComponent<Transform>("Transform");
    if (!transform) return worldVertices;

    const std::vector<float>& localFloats = m_Owner->GetVertices();
    mat4 modelMatrix = transform->GetModelMatrix();

    for (size_t i = 0; i < localFloats.size(); i += 3) 
    {
        vec4 localPosHomogenous(localFloats[i], localFloats[i + 1], localFloats[i + 2], 1.0f);

        vec4 worldPosHomogenous = modelMatrix * localPosHomogenous;

        worldVertices.push_back(vec3(worldPosHomogenous.x, worldPosHomogenous.y, worldPosHomogenous.z));
    }

    return worldVertices;
}

std::vector<vec3> Collider::GetAxes()
{
    std::vector<vec3> vertices = GetWorldVertices();
    std::vector<vec3> axes;
    for (int i = 0; i < vertices.size(); i++)
    {
        vec3 a = vertices[i];
        vec3 b = vertices[i+1 < vertices.size() ? i+1 : 0];

        vec3 edge = b - a;

        vec3 normal = vec3(-edge.y, edge.x, 0.0f);
        normal = normalize(normal);

        axes.push_back(normal);
    }
    return axes;
}

void Collider::PhysicsUpdate(float deltaTime)
{
    
}