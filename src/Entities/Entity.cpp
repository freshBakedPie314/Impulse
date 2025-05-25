#include "Entity.h"

Entity::Entity(Shape shape)
{
	std::vector<float> vertices = GetVetices(shape);
	std::vector<unsigned int> indices = GetIndices(shape);;
	m_localVertices = vertices;
	m_VBO = std::make_unique<VertexBuffer>(vertices.data(), sizeof(float) * vertices.size());
	VertexLayout layout;
	layout.Push<float>(3);
	m_VAO = std::make_unique<VertexArray>();
	m_VAO->AddBuffer(*m_VBO, layout);
	m_IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());

	std::string shaderPath = (shape == Shape::CIRCLE) ? "res/Default_Shader_Circle.shader" : "res/Default_Shader.shader";
	m_Shader = std::make_unique<Shader>(shaderPath);
}

Entity::~Entity()
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
	else if (shape == Shape::SQUARE || shape == Shape::CIRCLE)
	{
		return {
			//  x      y      z
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.5f,  0.5f,  0.0f,
			-0.5f,  0.5f,  0.0f
		};
	}
	else
	{
		return {};
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
	else if (shape == Shape::SQUARE || shape == Shape::CIRCLE)
	{
		return {
			0 , 1 , 2,
			2 , 3 , 0
		};
	}
	else
	{
		std::cout << "Warning: No Shape Specified" << std::endl;
		return {};
	}
}
