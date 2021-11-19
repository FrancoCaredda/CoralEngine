#include "Renderer.h"

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
