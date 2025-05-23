#include "RendererSystem.h"
#include <Component.h>

void RendererSystem::Update(Scene* scene)
{	
	m_CurrentScene = scene;
	for (auto a : scene->GetEntities())
	{
		a->GetShader()->SetUniform4mat("u_view", scene->GetViewMat());
		a->GetShader()->SetUniform4mat("u_projection", scene->GetProjectionMat());
		Transform* transformComponent = static_cast<Transform*>(a->GetComponent<Transform>("Transform"));
		vec3 pos = transformComponent->m_Position;
		vec3 rot = transformComponent->m_Rotation;
		mat4 model = createTranformationMatrix(pos, rot.z);
		a->GetShader()->SetUniform4mat("u_model", model);

		a->GetVAO()->Bind();
		a->GetShader()->Bind();
		glDrawElements(GL_TRIANGLES, a->GetIBO()->Size() , GL_UNSIGNED_INT, nullptr);
	}
}
