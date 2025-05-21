#pragma once
#include <vector>
#include <iostream>
#include "../Entities/Entity.h"

class Scene {
private:
	std::vector<Entity*> entities;
	mat4 m_Projection;
	mat4 m_View;
public:
	Scene();
	~Scene();
	void AddEntity(Entity* e);
	std::vector<Entity*> inline GetEntities() const { return entities; }

	inline void SetProjectionMat(mat4 projectionMat) { m_Projection = projectionMat; }
	inline mat4 GetProjectionMat() const { return m_Projection; }
	inline mat4 GetViewMat() const { return m_View; }
};