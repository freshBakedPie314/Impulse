#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory> 
#include <string> 

#include <Components.h>

#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Shader.h>

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
	std::vector<float> m_localVertices;
	
public:
	Entity(Shape shape);
	~Entity();

	Shape m_Shape;

	std::vector<float> GetVetices(Shape shape);
	std::vector<unsigned int> GetIndices(Shape shape);
	std::unordered_map<std::string, Component*> GetComponents() const { return m_Components; }
	VertexBuffer* GetVBO() const { return m_VBO.get(); }
	VertexArray* GetVAO() const { return m_VAO.get(); }
	IndexBuffer* GetIBO() const { return m_IBO.get(); }
	std::vector<float> GetVertices() const { return m_localVertices; }
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
