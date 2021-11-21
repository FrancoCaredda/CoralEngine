#include "Renderer.h"

#include "Components/Transform.h"

Renderer Renderer::s_Instance;

Renderer& Renderer::Get() noexcept
{
    return s_Instance;
}

void Renderer::Clear() noexcept
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::ClearColor(float r, float g, float b, float a) noexcept
{
    glClearColor(r, g, b, a);
}

void Renderer::PushTarget(Sprite* target) noexcept
{
    s_Instance.m_Targets.push_back(target);
}

void Renderer::PopTarget() noexcept
{
    s_Instance.m_Targets.pop_front();
}

void Renderer::DrawSpriteArrays() noexcept
{
    for (auto i = s_Instance.m_Targets.cbegin(); i != s_Instance.m_Targets.cend(); i++)
    {
        (*i)->Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}

void Renderer::Init() noexcept
{
    s_Instance.m_Projection = glm::ortho(0.0f, 600.0f, 0.0f, 480.0f);
}

void Renderer::SetCurrentCamera(Camera* camera) noexcept
{
    s_Instance.m_Camera = camera;
}

void Renderer::DrawObject(AGameObject* object) noexcept
{
    if (!object->HasComponent<Sprite>())
        return;

    Sprite* sprite = object->GetComponent<Sprite>();

    if (object->HasComponent<Transform>())
    {
        sprite->GetShaderProgram()->SetUniformMatrix("u_Model", object->GetComponent<Transform>()->GetTransform());
        sprite->GetShaderProgram()->SetUniformMatrix("u_View", s_Instance.m_Camera->GetComponent<Transform>()->GetTransform());
        sprite->GetShaderProgram()->SetUniformMatrix("u_Projection", s_Instance.m_Projection);
    }

    sprite->Bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
