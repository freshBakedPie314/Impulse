#pragma once
#include "Component.h"
#include <Maths.h>

class Transform : public Component{
public:
	vec3 m_Position;
	vec3 m_Rotation;
	vec3 m_Scale;
		
	Transform(const std::string& name, 
		vec3 postion = {0.0f , 0.0f ,0.f }, 
		vec3 rotation = { 0.0f , 0.0f ,0.f }, 
		vec3 scale = { 1.0f , 1.0f ,1.f });

	Transform(vec3 position = { 0.0f , 0.0f ,0.f },
		vec3 rotation = { 0.0f , 0.0f ,0.f },
		vec3 scale = { 1.0f , 1.0f ,1.f });
private:

};