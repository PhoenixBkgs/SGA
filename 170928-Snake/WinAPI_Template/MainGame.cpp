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
    //  head
    Player player;
    player.SetDirAngle(90);
    player.SetMoveSpeed(10.0f);
    player.SetType(UNIT_HEAD);
    player.m_unitSize = UnitSize{ UNIT_SIZE, UNIT_SIZE };
    player.SetPosition(UnitPos{ 300.0f, 300.0f });
    player.SetBodyRect(player.m_unitPos, player.m_unitSize);
    
    m_vecPlayer.push_back(player);

    for (int i = 0; i < 5; i++)
    {
        Player tPlayer;
        player.SetType(UNIT_BODY);
        tPlayer.SetMoveSpeedXY(UnitSpeed{ 0.0f, 0.0f });
        tPlayer.SetPosition(player.GetPosition());
        tPlayer.SetBodyRect(player.m_unitPos, player.m_unitSize);
        m_vecPlayer.push_back(tPlayer);
    }
}

void MainGame::Update()
{
    GameNode::Update();
    SystemController();

    if (m_isPlaying)
    {
        int randNum = rand() % 10000;
        if (randNum < 50)
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
            iter->SetPosition(tPos);
            iter->SetBodyRect(tPos, iter->m_unitSize);
            tPos = tPos2;
        }

        for (auto collIter = m_vecItem.begin(); collIter != m_vecItem.end();)
        {
            RECT tRt;
            if (IntersectRect(&tRt, &collIter->rtBody, m_vecPlayer[0].GetBodyRect()))
            {
                m_vecPlayer[0].SetMoveSpeed(m_vecPlayer[0].GetMoveSpeed() * collIter->slower);

                if (collIter->addition > 0)
                {
                    Player tPlayer;
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
        m_vecPlayer.begin()->SetMoveSpeed(m_vecPlayer.begin()->GetMoveSpeed() + 0.001f);
        Player player = m_vecPlayer[0];
        RECT rt = *player.GetBodyRect();
        if (rt.right >= W_WIDTH)
        {
            m_vecPlayer[0].SetDirAngle(180.0f - player.GetDirAngle());
        }
        if (rt.top <= 0)
        {
            player.m_moveSpeedXY.y *= -1.0f;
            m_vecPlayer[0].SetDirAngle(-player.GetDirAngle());
        }
        if (rt.left <= 0)
        {
            player.m_moveSpeedXY.x *= -1.0f;
            m_vecPlayer[0].SetDirAngle(180.0f - player.GetDirAngle());
        }
        if (rt.bottom >= W_HEIGHT)
        {
            player.m_moveSpeedXY.y *= -1.0f;
            m_vecPlayer[0].SetDirAngle(-player.GetDirAngle());
        }
        
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
        Rectangle(g_hDC, iter2->rtBody.left, iter2->rtBody.top, iter2->rtBody.right, iter2->rtBody.bottom);
    }
}

void MainGame::PlayerController()
{
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        m_vecPlayer[0].SumAngle(5.0f);
    }
    else if(g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        m_vecPlayer[0].SumAngle(-5.0f);
    }
}

void MainGame::SystemController()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        m_isPlaying = !m_isPlaying;
    }
}

void MainGame::GenItem()
{
    int genX = rand() % (W_WIDTH - 100);
    genX += 50;
    int genY = rand() % (W_HEIGHT - 100);
    genY += 50;

    tagItem tItem;
    tItem.rtBody.left = genX - 10;
    tItem.rtBody.right = genX + 10;
    tItem.rtBody.top = genY - 10;
    tItem.rtBody.bottom = genY + 10;
    tItem.addition = 0;
    tItem.slower = 1.0f;
    int attrNum = rand() % 100;
    if (attrNum >= 30)
    {
        tItem.addition = 1;
    }
    else if (attrNum >= 5)
    {
        tItem.slower = 0.8f;
    }
    else
    {
        tItem.addition = 1;
        tItem.slower = 1.2f;
    }
    m_vecItem.push_back(tItem);
}
