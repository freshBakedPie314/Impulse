#include "Entity.h"

Entity::Entity()
{
	float vertices[] = {
		//  x      y      z
		 0.0f,  0.5f,  0.0f,   // top vertex
		-0.5f, -0.5f,  0.0f,   // bottom left
		 0.5f, -0.5f,  0.0f    // bottom right
	};
	m_VBO = std::make_unique<VertexBuffer>(vertices , sizeof(vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

Entity::~Entity()
{

}

void Entity::AddComponent()
{
	
}

