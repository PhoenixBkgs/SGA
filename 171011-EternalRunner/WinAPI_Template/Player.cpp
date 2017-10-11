#include "stdafx.h"
#include "Player.h"
#include "Obstacle.h"
#include "Item.h"

Player::Player()
    :m_playerBuff(ITEM_END)
    , m_headUpMsg("NORMAL")
{
    m_unitPos.x = W_WIDTH  * 0.3f;
    m_unitPos.y = W_HEIGHT * 0.8f;
    m_unitSize = { PLAYER_WIDTH, PLAYER_HEIGHT };
    SetBodyRect(m_unitPos, m_unitSize);
    m_currDownForce = 5.0f;
}


Player::~Player()
{
}

void Player::Start()
{
    m_pImg->SetupForSprites(8, 0, PLAYER_WIDTH, PLAYER_HEIGHT, 10);
}

void Player::Update()
{
    SetBodyRect(m_unitPos, m_unitSize);

    switch (m_playerBuff)
    {
    case ITEM_IMMORTAL:
    case ITEM_MAGNET:
    case ITEM_GIANT:
    {
        m_buffTimer++;
        if (m_buffTimer > BUFF_DURING_TIME)
        {
            m_buffTimer = 0;
            m_playerBuff = ITEM_END;
            m_headUpMsg = "NORMAL";
            Reset();
        }
    }
        break;
    }

    //  APPLY GRAVITY
    switch (m_playerState)
    {
    case PLAYER_RUN:
        break;
    case PLAYER_JUMP:
        break;
    case PLAYER_DJUMP:
        break;
    }

    m_unitPos.y += m_currDownForce;
    m_currDownForce *= 1.009f;
    if (m_currDownForce > GRAVITY)
    {
        m_currDownForce = GRAVITY;
    }

    if (m_unitPos.y > W_HEIGHT * 0.8f)
    {
        m_unitPos.y = W_HEIGHT * 0.8f;
        m_currDownForce = 1.0f;
    }
    
    if (m_unitPos.y < 0.0f)
    {
        m_unitPos.y = 0.0f;
    }

    //  COLLISION OBSTACLE
    for (auto obsIter = m_vecObstacles->begin(); obsIter != m_vecObstacles->end(); obsIter++)
    {
        RECT rt;
        if (IntersectRect(&rt, &m_rtBody, obsIter->GetBodyRect()))
        {
            if (obsIter->GetLifeCount() > 0)
            {
                //  HAS COLLISION
                if (m_playerBuff == ITEM_IMMORTAL)
                {
                    obsIter->SetMoveSpeed(UnitSpeed{ -200.0f, -200.0f });
                }
                else
                {
                    m_LifeCount -= 1;
                }
                obsIter->SetLifeCount(0);
            }
        }
    }
    
    //  COLLISION ITEM
    for (auto iter = m_vecItems->begin(); iter != m_vecItems->end(); iter++)
    {
        RECT rt;
        E_ITEM_TYPE itemType = iter->GetItemType();
        if (IntersectRect(&rt, &m_rtBody, iter->GetBodyRect()))
        {
            iter->m_LifeCount = 0;
            if (itemType == ITEM_SCORE)
            {
                return;
            }

            switch (itemType)
            {
            case ITEM_IMMORTAL:
                m_headUpMsg = "IMMORTAL";
                m_buffTimer = 0;
                m_playerBuff = itemType;
                Reset();
                break;
            case ITEM_MAGNET:
                m_headUpMsg = "MAGNET";
                m_buffTimer = 0;
                m_playerBuff = itemType;
                Reset();
                break;
            case ITEM_GIANT:
                m_headUpMsg = "GIANT";
                m_buffTimer = 0;
                m_unitSize = { 216, 280 };
                m_playerBuff = itemType;
                break;
            }
        }
    }

    if (m_playerBuff == ITEM_MAGNET)
    {
        for (auto iter = m_vecItems->begin(); iter != m_vecItems->end(); iter++)
        {
            UnitPos pos = iter->GetPosition();
            double distance = m_geoHelper.GetDistance(m_unitPos, pos);
            if (distance < 500.0f)
            {
                double angle = m_geoHelper.GetAngleFromCoord(pos, m_unitPos);
                UnitSpeed speed = m_geoHelper.GetCoordFromAngle(angle, 10.0f);
                iter->SetMoveSpeed(speed);
            }
        }
    }
}

void Player::Render()
{
    switch (m_playerBuff)
    {
    case ITEM_IMMORTAL:
    case ITEM_MAGNET:
    case ITEM_GIANT:
        Rectangle(g_hDC, m_rtBody.left, m_rtBody.top - 25, m_rtBody.right - (int)(m_buffTimer * 0.5f), m_rtBody.top);
        break;
    default:
        break;
    }
    m_pImg->SpritesRender(g_hDC, m_rtBody, 255);
#ifdef _DEBUG
    char infoMsg[100];
    sprintf_s(infoMsg, m_headUpMsg.data());
    TextOut(g_hDC, (int)m_unitPos.x, (int)m_unitPos.y, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG

}

void Player::Reset()
{
    m_unitSize = { PLAYER_WIDTH, PLAYER_HEIGHT };
}
