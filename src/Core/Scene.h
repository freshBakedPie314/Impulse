#pragma once
#include <vector>
#include <iostream>
#include "../Entities/Entity.h"

class Scene {
private:
	std::vector<Entity*> entities;
	mat4 m_Projection;
	mat4 m_View;
	vec3 m_cameraPos;
public:
	Scene();
	~Scene();
	void AddEntity(Entity* e);
	std::vector<Entity*> inline GetEntities() const { return entities; }

	inline void SetProjectionMat(mat4 projectionMat) { m_Projection = projectionMat; }
	inline mat4 GetProjectionMat() const { return m_Projection; }

	inline void SetViewMat(vec3 camera) {
		m_cameraPos = camera;
		vec3 to = camera;
		to.z -= 1.0f;
		m_View = lookAt(camera, to);
	}
	inline mat4 GetViewMat() const { return m_View; }
	inline vec3 GetCameraPos() const { return m_cameraPos; }
};