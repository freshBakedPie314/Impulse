#include "Scene.h"

Scene::Scene()
{
	vec3 camera = { 0.5f , 0.0f , 1.0f };
	vec3 to = camera;
	to.z -= 1.0f;
	m_View = lookAt(camera, to);

	m_Projection = projectionOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
}

Scene::~Scene()
{

}

void Scene::AddEntity(Entity* e)
{
	entities.push_back(e);
}
