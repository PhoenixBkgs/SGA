#include "stdafx.h"
#include "Player.h"
#include "Obstacle.h"
#include "Item.h"
#include "Hole.h"

Player::Player()
    : m_playerBuff(ITEM_END)
    , m_headUpMsg("NORMAL")
    , m_money(0)
    , m_isFloorExist(true)
{
    m_unitPos.x = W_WIDTH  * 0.3f;
    m_unitPos.y = FLOOR_POS_Y;
    m_unitSize = { PLAYER_WIDTH, PLAYER_HEIGHT };
    SetBodyRect(m_unitPos, m_unitSize);
    m_currDownForce = INIT_DOWNFORCE;
    m_bBrush = new HBRUSH;
}


Player::~Player()
{
    delete m_bBrush;
}

void Player::Start()
{
    m_pImg->SetupForSprites(8, 0, PLAYER_WIDTH, PLAYER_HEIGHT, 10);
    m_playerState = PLAYER_RUN;
    *m_bBrush = CreateSolidBrush(RGB(0, 255, 0));
}

void Player::Update()
{
    Move();
    m_isFloorExist = true;
    for (auto holeCollIter = m_vecHoles->begin(); holeCollIter != m_vecHoles->end(); holeCollIter++)
    {
        RECT holeRt = holeCollIter->m_rtBody;
        RECT rt;
        if (IntersectRect(&rt, &m_rtBody, &holeRt))
        {
            m_isFloorExist = false;
        }

        if ((int)m_unitPos.x > holeRt.left &&
            (int)m_unitPos.x < holeRt.right)
        {
            m_isFloorExist = false;
        }

        if (m_rtBody.left < holeRt.right &&
            m_rtBody.left > holeRt.left)
        {
            if (m_rtBody.bottom > holeRt.top)
            {
                m_isFloorExist = false;
            }
        }
    }

    if (m_unitPos.y + m_moveSpeed.y > FLOOR_POS_Y - m_unitSize.h / 2)
    {
        if (m_isFloorExist)
        {
            m_playerState = PLAYER_RUN;
            m_currDownForce = INIT_DOWNFORCE;
            m_unitPos.y = FLOOR_POS_Y - m_unitSize.h / 2;
            m_moveSpeed.y = 0.0f;
        }
        else
        {
        }
    }


    if (m_unitPos.y < 0.0f)
    {
        m_unitPos.y = 0.0f;
    }
    m_moveSpeed.y += m_currDownForce;
    
    m_rtBody = SetBodyRect(m_unitPos, m_unitSize, 0);
    m_hitBox = SetBodyRect(m_unitPos, m_unitSize, 30);

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
        break;
    }
    }

    //  COLLISION OBSTACLE
    for (auto obsIter = m_vecObstacles->begin(); obsIter != m_vecObstacles->end(); obsIter++)
    {
        RECT rt;
        if (IntersectRect(&rt, &m_hitBox, obsIter->GetBodyRect()))
        {
            //  HAS COLLISION
            if (m_playerBuff == ITEM_IMMORTAL)
            {
                obsIter->SetMoveSpeed(UnitSpeed{ -200.0f, -200.0f });
                obsIter->SetMovable(false);
            }
            else
            {
                if (obsIter->IsActive())
                {
                    m_LifeCount -= 1;
                    obsIter->Deactivate();
                }
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
                m_score += 100;
                m_money += iter->GetMoney();
                return;
            }

            switch (itemType)
            {
            case ITEM_IMMORTAL:
                m_headUpMsg = "IMMORTAL";
                m_buffTimer = 0;
                m_playerBuff = itemType;
                m_score += 200;
                Reset();
                break;
            case ITEM_MAGNET:
                m_headUpMsg = "MAGNET";
                m_buffTimer = 0;
                m_playerBuff = itemType;
                m_score += 50;
                Reset();
                break;
            case ITEM_GIANT:
                m_headUpMsg = "GIANT";
                m_buffTimer = 0;
                m_unitSize = { 216, 280 };
                m_playerBuff = itemType;
                m_score += 1000;
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
            if (distance < 1000.0f)
            {
                double angle = m_geoHelper.GetAngleFromCoord(pos, m_unitPos);
                UnitSpeed speed = m_geoHelper.GetCoordFromAngle(angle, 50.0f);
                iter->SetMoveSpeed(speed);
            }
        }
    }

    if (m_unitPos.y > (double)W_HEIGHT)
    {
        //  PLAYER DEAD
        SetLifeCount(0);
    }
}

void Player::Render()
{
    switch (m_playerBuff)
    {
    case ITEM_IMMORTAL:
    case ITEM_MAGNET:
    case ITEM_GIANT:
    {
        RECT tRect = { m_rtBody.left, m_rtBody.top - 25, m_rtBody.right - (int)(m_buffTimer * 0.5f), m_rtBody.top };
        FillRect(g_hDC, &tRect, *m_bBrush);
        break;
    }
    default:
        break;
    }
    m_pImg->SpritesRender(g_hDC, m_rtBody, 255);
#ifdef _DEBUG
    m_drawHelper.DrawBoxLine2D(m_hitBox, 3, _RGBA{ 100, 255, 100, 0 });
    char infoMsg[100];
    sprintf_s(infoMsg, m_headUpMsg.data());
    TextOut(g_hDC, (int)m_unitPos.x, (int)m_unitPos.y, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void Player::Reset()
{
    m_unitSize = { PLAYER_WIDTH, PLAYER_HEIGHT };
}
