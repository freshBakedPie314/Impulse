#pragma once
#include <vector>
#include <iostream>
#include <../Entities/Entity.h>

class Scene {
private:
	std::vector<Entity*> entities;
public:
	Scene();
	~Scene();
	void AddEntity(Entity* e);
	std::vector<Entity*> inline GetEntities() const { return entities; }
};