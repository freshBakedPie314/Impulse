#include "VertexBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer(float vertices[] , unsigned int size)
{
	glGenBuffers(1, &m_id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
