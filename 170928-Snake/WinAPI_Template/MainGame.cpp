#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    Start();
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
    m_brushPlayer = CreateSolidBrush(RGB(10, 250, 10));
    m_brushItem1 = CreateSolidBrush(RGB(200, 50, 50));
    m_brushItem2 = CreateSolidBrush(RGB(50, 200, 50));
    m_brushItem3 = CreateSolidBrush(RGB(50, 50, 200));

    //  head
    Player player;
    player.SetDirAngle(90);
    player.SetMoveSpeed(10.0f);
    player.SetType(UNIT_HEAD);
    player.m_unitSize = UnitSize{ UNIT_SIZE, UNIT_SIZE };
    player.SetPosition(UnitPos{ 300.0f, 300.0f });
    player.SetBodyRect(player.m_unitPos, player.m_unitSize);
    player.SetBrush(&m_brushPlayer);
    m_vecPlayer.push_back(player);

    m_isReal = false;
    m_isAutoPlaying = false;
    m_prevGameScore = -1;
    m_gameScore = 0;
    m_itemCount = 0;
    m_aiWaitCount = MAX_AI_WAIT;
}

void MainGame::Update()
{
    GameNode::Update();
    SystemController();

    if (m_isPlaying)
    {
        int randNum = rand() % 10000;
        if (randNum < 750)
        {
            //  gen item
            GenItem();
        }
        PlayerController();
        UnitPos tPos = m_vecPlayer.begin()->GetPosition();
        UnitPos tPos2;
        for (auto iter = m_vecPlayer.begin(); iter != m_vecPlayer.end(); iter++)
        {
            tPos2 = iter->GetPosition();
            double dLen = m_geoHelper.GetDistance(tPos, tPos2);
            double dAngle = m_geoHelper.GetAngleFromCoord(tPos2, tPos);
            iter->SetMoveSpeedXY(m_geoHelper.GetCoordFromAngle(dAngle, dLen));
            if (m_isReal)
            {
                if (dLen > UNIT_SIZE * 0.7f)
                {
                    iter->Move();
                }
                tPos = tPos2;
            }
            else
            {
                if (dLen > UNIT_SIZE * 0.5f)
                {
                    iter->Move();
                }
                tPos = tPos2;
                /*
                tPos2 = iter->GetPosition();
                iter->SetPosition(tPos);
                iter->SetBodyRect(tPos, iter->m_unitSize);
                tPos = tPos2;
                */
            }
        }

        for (auto collIter = m_vecItem.begin(); collIter != m_vecItem.end();)
        {
            RECT tRt;
            if (IntersectRect(&tRt, &collIter->rtBody, m_vecPlayer[0].GetBodyRect()))
            {
                m_vecPlayer[0].SetMoveSpeed(m_vecPlayer[0].GetMoveSpeed() * collIter->accel);

                m_prevGameScore = -1;
                if (collIter->addition > 0)
                {
                    Player tPlayer;
                    tPlayer.SetBrush(&m_brushPlayer);
                    tPlayer.SetType(UNIT_BODY);
                    tPlayer.SetMoveSpeedXY(UnitSpeed{ 0.0f, 0.0f });
                    tPlayer.SetPosition((m_vecPlayer.end() - 1)->GetPosition());
                    tPlayer.SetBodyRect(m_vecPlayer[0].m_unitPos, m_vecPlayer[0].m_unitSize);
                    m_vecPlayer.push_back(tPlayer);
                }
                collIter = m_vecItem.erase(collIter);
            }
            else
            {
                collIter++;
            }
        }

        m_vecPlayer.begin()->Update();
        m_vecPlayer.begin()->SetMoveSpeed(m_vecPlayer.begin()->GetMoveSpeed() + 0.01f);
        Player player = m_vecPlayer[0];
        RECT rt = *player.GetBodyRect();
        if (rt.right >= W_WIDTH)
        {
            m_vecPlayer[0].SetDirAngle(180.0f - player.GetDirAngle());
            m_prevGameScore = -1;
        }
        if (rt.top <= 0)
        {
            m_vecPlayer[0].SetDirAngle(-player.GetDirAngle());
            m_prevGameScore = -1;
        }
        if (rt.left <= 0)
        {
            m_vecPlayer[0].SetDirAngle(180.0f - player.GetDirAngle());
            m_prevGameScore = -1;
        }
        if (rt.bottom >= W_HEIGHT)
        {
            m_vecPlayer[0].SetDirAngle(-player.GetDirAngle());
            m_prevGameScore = -1;
        }
        m_gameScore = m_vecPlayer.size();
    }
}

void MainGame::Render()
{
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    for (auto iter = m_vecPlayer.begin(); iter != m_vecPlayer.end(); iter++)
    {
        iter->Render();
    }

    for (auto iter2 = m_vecItem.begin(); iter2 != m_vecItem.end(); iter2++)
    {
        HPEN hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
        SelectObject(g_hDC, hPen);

        switch (iter2->itemType)
        {
        case ITEM_TYPE_1:
            SelectObject(g_hDC, m_brushItem1);
            break;
        case ITEM_TYPE_2:
            SelectObject(g_hDC, m_brushItem2);
            break;
        case ITEM_TYPE_3:
            SelectObject(g_hDC, m_brushItem3);
            break;
        }
        Ellipse(g_hDC, iter2->rtBody.left, iter2->rtBody.top, iter2->rtBody.right, iter2->rtBody.bottom);
        DeleteObject(hPen);
        GetStockObject(WHITE_BRUSH);

    }
    UserInterfaceRender();
}

void MainGame::UserInterfaceRender()
{
    char strScore[MAXCHAR];
    sprintf(strScore, "Score : %d   Item Remain : %d", m_gameScore, m_itemCount);
    m_drawHelper.DrawStatusText(strScore, 20, _RGBA{ 0, 0, 0, 0 }, TEXT("Consolas"));
}

void MainGame::PlayerController()
{
    if (m_isAutoPlaying)
    {
        if (m_prevGameScore != m_gameScore)
        {
            //int targetIdx = rand() % (m_vecItem.size() - 1);  LEGACY
            //int targetPosX = m_vecItem[targetIdx].rtBody.left + 10;   LEGACY
            //int targetPosY = m_vecItem[targetIdx].rtBody.top + 10;    LEGACY
            double prevDist = 1000000.0f;
            double currDist = 0.0f;
            UnitPos targetPos;
            UnitPos tempTargetPos;
            UnitPos headPos = m_vecPlayer[0].GetPosition();
            for (auto iter = m_vecItem.begin(); iter != m_vecItem.end(); iter++)
            {
                currDist = m_geoHelper.GetDistance(headPos, iter->Pos);
                if (currDist < prevDist)
                {
                    prevDist = currDist;
                    targetPos = iter->Pos;
                }
            }
            if (m_vecItem.size() > 0)
            {
                m_targetAngle = m_geoHelper.GetAngleFromCoord(headPos, targetPos);
            }

            m_prevGameScore = m_gameScore;
            m_aiWaitCount = MAX_AI_WAIT;
        }
        else
        {
            if (m_aiWaitCount <= 0)
            {
                m_prevGameScore = -1;
                m_aiWaitCount = MAX_AI_WAIT;
            }

            double dirAngle = m_vecPlayer[0].GetDirAngle();
            if (m_vecItem.size() > 0)
            {
                m_vecPlayer[0].SetDirAngle(m_targetAngle);
            }
            /*
            if (m_targetAngle >= m_vecPlayer[0].GetDirAngle())
            {
                //m_vecPlayer[0].SumAngle(abs(m_targetAngle - dirAngle) * 0.25);
                m_vecPlayer[0].SumAngle(HANDLE_TICK);
            }
            else if(m_targetAngle <= m_vecPlayer[0].GetDirAngle())
            {
                //m_vecPlayer[0].SumAngle(-abs(m_targetAngle - dirAngle) * 0.25);
                m_vecPlayer[0].SumAngle(-HANDLE_TICK);
            }
            */
            m_aiWaitCount--;
        }
    }
    else
    {
        if (g_pKeyManager->isStayKeyDown(VK_LEFT))
        {
            m_vecPlayer[0].SumAngle(HANDLE_TICK);
        }
        else if(g_pKeyManager->isStayKeyDown(VK_RIGHT))
        {
            m_vecPlayer[0].SumAngle(-HANDLE_TICK);
        }
    }
}

void MainGame::SystemController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        m_isPlaying = !m_isPlaying;
    }
    if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
    {
        m_isAutoPlaying = !m_isAutoPlaying;
    }
    if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
    {
        m_isReal = !m_isReal;
    }
}

void MainGame::GenItem()
{
    int genX = rand() % (W_WIDTH - 100);
    genX += 50;
    int genY = rand() % (W_HEIGHT - 100);
    genY += 50;

    tagItem tItem;
    tItem.Pos = { (double)genX, (double)genY };
    tItem.rtBody.left = genX - 10;
    tItem.rtBody.right = genX + 10;
    tItem.rtBody.top = genY - 10;
    tItem.rtBody.bottom = genY + 10;
    tItem.addition = 0;
    tItem.accel = 1.0f;
    int attrNum = rand() % 100;
    if (attrNum >= 30)
    {
        tItem.addition = 1;
        tItem.itemType = ITEM_TYPE_1;
    }
    else if (attrNum >= 5)
    {
        tItem.accel = 0.8f;
        tItem.itemType = ITEM_TYPE_2;
    }
    else
    {
        tItem.addition = 1;
        tItem.accel = 1.2f;
        tItem.itemType = ITEM_TYPE_3;
    }
    m_vecItem.push_back(tItem);
    m_itemCount++;
}


