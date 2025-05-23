#pragma once
#include <string>

class Entity;

class Component {
public:
	std::string m_name;
	Entity* m_Owner = nullptr;

	Component(const std::string& name) : m_name(name), m_Owner(nullptr) {};
	virtual ~Component() = default;

	
	
	virtual void OnAddedToEntity(Entity* owner) { m_Owner = owner; }
};

