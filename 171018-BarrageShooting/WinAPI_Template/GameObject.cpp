#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject()
    : m_bIsSetup(false)
    , m_isImmortal(false)
{
    Setup();
    SetBodyImgAuto();
}

GameObject::GameObject(string szTagName)
    : m_bIsSetup(false)
    , m_isImmortal(false)
{
    Setup();
    SetTagName(szTagName);
}

GameObject::~GameObject()
{
}

void GameObject::Setup()
{
    m_uId = -1;
    m_szTagName = "none";
    m_imgBody = NULL;
    m_dPos = UnitPos{ W_WIDTH * 0.5f, W_HEIGHT * 0.5f };
    m_dSpeed = UnitPos{ 0.0f, 0.0f };
    m_nSize = UnitSize{ 1, 1 };
    m_isVisible = true;
    m_isAlive = true;
    m_dAlpha = 255.0f;
    m_dAngle = 0.0f;
    m_isLockInWnd = false;
    m_bIsSetup = true;
    m_rtLockArea = { 0, 0, W_WIDTH, W_HEIGHT };
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

void GameObject::SetHBox()
{
    m_rtHitBox = { m_rtBody.left + m_nMarginHBox.left, m_rtBody.top + m_nMarginHBox.top
                 , m_rtBody.right - m_nMarginHBox.right, m_rtBody.bottom - m_nMarginHBox.bottom };
    m_nSizeHBox = g_pDrawHelper->GetSizeFromRect(m_rtHitBox);
}

void GameObject::SetBodyImgAuto()
{
    SetBodyImgByKey(m_szTagName);
}

void GameObject::Update()
{
    if (m_bIsSetup)
    {
        if (m_isLockInWnd)
        {
            WndLocker();
        }
        Move();
    }
}

void GameObject::Render()
{
#ifdef _DEBUG
    if (m_bIsSetup)
    {
        if (m_isVisible == true)
        {
            g_pDrawHelper->DrawBoxLine2D(m_rtBody, 5, _RGBA{ 0, 0, 0, 0 });         //  Draw body rect
            g_pDrawHelper->DrawBoxLine2D(m_rtHitBox, 2, _RGBA{ 0, 255, 0, 0 });     //  Draw hit box rect
        }
    }
#endif // _DEBUG
}

void GameObject::Move()
{
    m_dPos.x += m_dSpeed.x;
    m_dPos.y += m_dSpeed.y;
    //  RECT UPDATE
    m_rtBody = g_pDrawHelper->MakeRect(m_dPos, m_nSize);
    SetHBox();
}

void GameObject::Setup(UnitPos Pos, UnitSize Size)
{
    SetBodyPos(Pos);
    SetBodySize(Size);
    SetBodyRect(g_pDrawHelper->MakeRect(m_dPos, m_nSize));
    SetHBox();
}

void GameObject::WndLocker()
{
    double hWidth = (double)m_nSize.w * 0.5f;
    double hHeight = (double)m_nSize.h * 0.5f;
    
    m_dPos.x = max(m_rtLockArea.left + hWidth, m_dPos.x);
    m_dPos.y = max(m_rtLockArea.top + hWidth, m_dPos.y);
    m_dPos.x = min(m_rtLockArea.right - hWidth, m_dPos.x);
    m_dPos.y = min(m_rtLockArea.bottom - hHeight, m_dPos.y);
}
