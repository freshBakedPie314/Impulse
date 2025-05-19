#pragma once
#include <iostream>
#include <vector>
#include <memory> 
#include "../Utilities/VertexBuffer.h"

class Entity {
private:
	std::vector<int> m_Componets;
	std::unique_ptr<VertexBuffer> m_VBO;

public:
	Entity();
	~Entity();

	void AddComponent();
	std::vector<int> GetComponets() const { return m_Componets; }
	VertexBuffer* GetVBO() const { return m_VBO.get(); }
};
