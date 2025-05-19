#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::AddEntity(Entity* e)
{
	entities.push_back(e);
	std::cout << "Added Entity" << std::endl;
}
