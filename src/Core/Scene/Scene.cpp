#include "Scene.h"

Scene::Scene()
{
	vec3 camera = { 0.5f , 0.0f , 1.0f };
	m_cameraPos = camera;
	vec3 to = camera;
	to.z -= 1.0f;
	m_View = lookAt(camera, to);

	m_Projection = projectionOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
}

Scene::~Scene()
{

}

void Scene::AddEntity(std::string name, std::unique_ptr<Entity> entity)
{
	if (m_entities.find(name) != m_entities.end())
	{
		std::cerr << "Cannot have Entites with same name in the same Scene" << std::endl;
		std::cerr << "[Entity]: " << name << std::endl;
		return;
	}
	m_entities[name] = std::move(entity);
}


std::vector<Entity*> Scene::GetEntities() const 
{
	std::vector<Entity*> raw_pointers;
	raw_pointers.reserve(m_entities.size());
	for (const auto& entity_ptr : m_entities) {
		raw_pointers.push_back(entity_ptr.second.get());
	}
	return raw_pointers;
}

Entity* Scene::GetEntitiy(std::string name) const
{
	if (m_entities.find(name) != m_entities.end()) return m_entities.find(name)->second.get();
	else return nullptr;
}