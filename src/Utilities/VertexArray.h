#pragma once
#include "VertexLayout.h"
#include "VertexBuffer.h"

class VertexLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:

	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer( VertexBuffer& vb,  VertexLayout& layout);
};
