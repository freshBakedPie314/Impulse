#include <VertexBuffer.h>
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
}

Entity::~Entity()
{

}

void Entity::AddComponent()
{
	
}

