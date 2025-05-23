#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory> 
#include <string> 

#include "../Components/Component.h"
#include "../Components/Transform.h"

#include "../Utilities/VertexBuffer.h"
#include "../Utilities/IndexBuffer.h"
#include "../Utilities/VertexArray.h"
#include "../Utilities/Shader.h"

class Transform;

enum struct Shape {
	TRIANGLE,
	SQUARE,
	CIRCLE
};

class Entity {
private:
	std::unordered_map<std::string , Component*> m_Components;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;

public:
	Entity(Shape shape);
	~Entity();

	std::vector<float> GetVetices(Shape shape);
	std::vector<unsigned int> GetIndices(Shape shape);
	std::unordered_map<std::string, Component*> GetComponents() const { return m_Components; }
	VertexBuffer* GetVBO() const { return m_VBO.get(); }
	VertexArray* GetVAO() const { return m_VAO.get(); }
	IndexBuffer* GetIBO() const { return m_IBO.get(); }
	Shader* GetShader() const { return m_Shader.get(); }

	template <typename T, typename... Args>
	void AddComponent(const std::string& name, Args&&... args)
	{
		T* newComponent = new T(std::forward<Args>(args)...);
		m_Components[name] = newComponent;
		newComponent->OnAddedToEntity(this);
	}

	template<typename T>
	T* GetComponent(const std::string& name) const {
		auto it = m_Components.find(name);
		if (it != m_Components.end()) {
			return static_cast<T*>(it->second);
		}
		return nullptr;
	}
};
