#pragma once
#include "../../dependencies/GLEW/include/GL/glew.h"
#include "../../dependencies/GLFW/include/GLFW/glfw3.h"
#include "VertexLayout.h"

class VertexBuffer {
private:
	unsigned int m_id;
public:
	VertexBuffer(float vertices[] , unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};