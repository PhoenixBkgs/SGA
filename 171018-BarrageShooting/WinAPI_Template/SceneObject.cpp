#include "stdafx.h"
#include "SceneObject.h"

void SceneObject::Render()
{
    GameObject::Render();
    m_imgBody->Render(g_hDC, m_dPos);
}

void SceneObject::Setup(ImageObject * Image, UnitPos Pos)
{
    SetBodyImg(Image);
    SetBodyPos(Pos);
    SetBodySize(UnitSize{ m_imgBody->GetWidth(), m_imgBody->GetHeight() });
}
