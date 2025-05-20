#include "Entity.h"

Entity::Entity(Shape shape)
{
	std::vector<float> vertices = GetVetices(shape);
	std::vector<unsigned int> indices = GetIndices(shape);;

	m_VBO = std::make_unique<VertexBuffer>(vertices.data(), sizeof(float) * vertices.size());
	VertexLayout layout;
	layout.Push<float>(3);
	m_VAO = std::make_unique<VertexArray>();
	m_VAO->AddBuffer(*m_VBO, layout);
	m_IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());

	m_Shader = std::make_unique<Shader>("res/Default_Shader.shader");
}

Entity::~Entity()
{

}

void Entity::AddComponent()
{
	
}

std::vector<float> Entity::GetVetices(Shape shape)
{
	if (shape == Shape::TRIANGLE)
	{
		return {
			//  x      y      z
			 0.0f,  0.5f,  0.0f,
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f
		};
	}
	else if (shape == Shape::SQUARE)
	{
		return {
			//  x      y      z
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.5f,  0.5f,  0.0f,
			-0.5f,  0.5f,  0.0f
		};
	}
}

std::vector<unsigned int> Entity::GetIndices(Shape shape)
{
	if (shape == Shape::TRIANGLE)
	{
		return {
			0 , 1 , 2
		};
	}
	else if (shape == Shape::SQUARE)
	{
		return {
			0 , 1 , 2,
			2 , 3 , 0
		};
	}
}
