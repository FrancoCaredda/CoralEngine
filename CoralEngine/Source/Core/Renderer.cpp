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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(float r, float g, float b, float a) noexcept
{
    glClearColor(r, g, b, a);
}

#ifdef _DEBUG
void Renderer::Mode(RenderMode mode) noexcept
{
    switch (mode)
    {
    case FILL:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case LINE:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case POINT:
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    default:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }
}
#endif // _DEBUG

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

    if (sprite->m_TextureHandle != nullptr)
        sprite->m_Shader->SetUniformImage("u_Texture", sprite->m_TextureHandle.GetData());

    sprite->m_Shader->SetUniformMatrix("u_Model", object->GetComponent<Transform>()->GetTransform());
    sprite->m_Shader->SetUniformMatrix("u_View", s_Instance.m_Camera->GetComponent<Transform>()->GetTransform());
    sprite->m_Shader->SetUniformMatrix("u_Projection", s_Instance.m_Projection);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::Shutdown() noexcept
{
}
