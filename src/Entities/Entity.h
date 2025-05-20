#pragma once
#include <iostream>
#include <vector>
#include <memory> 
#include "../Utilities/VertexBuffer.h"
#include "../Utilities/IndexBuffer.h"
#include "../Utilities/VertexArray.h"
#include "../Utilities/Shader.h"

enum struct Shape {
	TRIANGLE,
	SQUARE
};

class Entity {
private:
	std::vector<int> m_Componets;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;

public:
	Entity(Shape shape);
	~Entity();

	void AddComponent();
	std::vector<float> GetVetices(Shape shape);
	std::vector<unsigned int> GetIndices(Shape shape);
	std::vector<int> GetComponets() const { return m_Componets; }
	VertexBuffer* GetVBO() const { return m_VBO.get(); }
	VertexArray* GetVAO() const { return m_VAO.get(); }
	IndexBuffer* GetIBO() const { return m_IBO.get(); }
	Shader* GetShader() const { return m_Shader.get(); }
};
