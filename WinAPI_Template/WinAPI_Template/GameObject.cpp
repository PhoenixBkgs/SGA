#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
    : m_uId(-1)
    , m_szTagName("none")
    , m_imgBody(NULL)
    , m_dPos(UnitPos{ W_WIDTH * 0.5f, W_HEIGHT * 0.5f })
    , m_dSpeed(UnitPos{ 0.0f, 0.0f })
    , m_nSize(UnitSize{ 1, 1 })
    , m_isVisible(true)
    , m_isAlive(true)
    , m_dAlpha(0.0f)
    , m_dAngle(0.0f)
{
    SetBodyImgAuto();
}

GameObject::~GameObject()
{
}

void GameObject::SetBodyRect(RECT Rect)
{
    m_rtBody = Rect;
    m_nSize = g_pDrawHelper->GetSizeFromRect(m_rtBody);
    m_dPos = g_pDrawHelper->GetPosFromRect(m_rtBody);
}

void GameObject::SetBodyImgByKey(string Key, bool IsOverwrite)
{
    if (Key == "none")
    {
        m_imgBody = NULL;
        return;
    }

    if (m_imgBody == NULL)
    {
        m_imgBody = g_pImgManager->FindImage(Key);
    }
    else
    {
        if (IsOverwrite == true)
        {
            m_imgBody = g_pImgManager->FindImage(Key);
        }
    }
}

void GameObject::SetBodyImgAuto()
{
    SetBodyImgByKey(m_szTagName);
}

void GameObject::Update()
{
    Move();
}

void GameObject::Render()
{
    if (m_isVisible == true)
    {
        if (m_imgBody != NULL)
        {
            m_imgBody->Render(g_hDC, m_rtBody.left, m_rtBody.top, m_nSize.w, m_nSize.h);
        }
    }
#ifdef _DEBUG
    g_pDrawHelper->DrawBoxLine2D(m_rtBody, 5, _RGBA{ 0, 0, 0, 0 });         //  Draw body rect
    g_pDrawHelper->DrawBoxLine2D(m_rtHitBox, 2, _RGBA{ 0, 255, 0, 0 });     //  Draw hit box rect
#endif // _DEBUG
}

void GameObject::Move()
{
    m_dPos.x += m_dSpeed.x;
    m_dPos.y += m_dSpeed.y;
    //  RECT UPDATE
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
}
