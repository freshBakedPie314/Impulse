#include "RendererSystem.h"

void RendererSystem::Update(Scene* scene)
{	
	m_CurrentScene = scene;
	for (auto a : scene->GetEntities())
	{
		a->GetShader()->SetUniform4mat("u_view", scene->GetViewMat());
		a->GetShader()->SetUniform4mat("u_projection", scene->GetProjectionMat());

		a->GetVAO()->Bind();
		a->GetShader()->Bind();
		glDrawElements(GL_TRIANGLES, a->GetIBO()->Size() , GL_UNSIGNED_INT, nullptr);
	}
}
