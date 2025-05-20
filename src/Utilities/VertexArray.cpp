#include "VertexLayout.h"
#include "VertexArray.h"

VertexArray::VertexArray() : m_RendererID(0)
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer( VertexBuffer& vb, VertexLayout& layout)
{
	Bind();
	vb.Bind();
	auto& attributes = layout.GetAttributes();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < attributes.size(); i++)
	{
		glEnableVertexAttribArray(i);
		auto& attribute = attributes[i];
		glVertexAttribPointer(i, attribute.count, attribute.type,
			attribute.normalised, layout.GetStride(), (const void*)offset);

		offset += attribute.GetSizeFromType(attribute.type) * attribute.count;
	}
}
