#pragma once
#include <vector>
#include <stdexcept>
#include "../../dependencies/GLEW/include/GL/glew.h"
#include "../../dependencies/GLFW/include/GLFW/glfw3.h"

struct VertexLayoutAttributes {
	unsigned int count;
	unsigned int type;
	unsigned char normalised;

	static unsigned int GetSizeFromType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		return 0;
	}
};

class VertexLayout {
private:
	std::vector<VertexLayoutAttributes> m_attributes;
	unsigned int m_stride;
public:

	VertexLayout() : m_stride(0) {};

	template <typename T>
	void Push(unsigned int count)
	{
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_attributes.push_back({count, GL_FLOAT , GL_FALSE });
		m_stride += count * VertexLayoutAttributes::GetSizeFromType(GL_FLOAT);
	}

	inline const std::vector<VertexLayoutAttributes>& GetAttributes() const { return m_attributes; }
	inline const unsigned int GetStride() { return m_stride; }
};