#include "Renderer.h"

#include "Components/Transform.h"

Renderer Renderer::s_Instance;

void Renderer::Init() noexcept
{
    s_Instance.m_Projection = glm::ortho(0.0f, 600.0f, 0.0f, 480.0f);
}

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

void Renderer::SetCurrentCamera(Camera* camera) noexcept
{
    s_Instance.m_Camera = camera;
}

void Renderer::DrawObject(AGameObject* object) noexcept
{
    if (!object->HasComponent<Sprite>())
        return;

    Sprite* sprite = object->GetComponent<Sprite>();

    sprite->Bind();

    sprite->m_Shader->SetUniformVector("u_Color", sprite->m_Color);

    if (sprite->m_Texture != nullptr)
        sprite->m_Shader->SetUniformImage("u_Texture",  sprite->m_Texture->GetSlot());

    if (object->HasComponent<Transform>())
    {
        sprite->m_Shader->SetUniformMatrix("u_Model", object->GetComponent<Transform>()->GetTransform());
        sprite->m_Shader->SetUniformMatrix("u_View", s_Instance.m_Camera->GetComponent<Transform>()->GetTransform());
        sprite->m_Shader->SetUniformMatrix("u_Projection", s_Instance.m_Projection);
    }


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::Shutdown() noexcept
{
}
