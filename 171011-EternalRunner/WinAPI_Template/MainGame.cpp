#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame():
    m_itemGenDelayCount(0),
    m_obsGenDelayCount(0)
{
    Start();
}


MainGame::~MainGame()
{
    delete m_bgImg;
    delete m_playerImg;
    delete m_scoreItemImg;
    delete m_giantItemImg;
    delete m_immortalItemImg;
    delete m_magnetItemImg;
}

void MainGame::Start()
{
    m_currGameState = GAME_READY;

    //  Set BG
    m_bgImg = new ImageKomastar;
    m_bgImg->Setup("images/bg.bmp", BG_WIDTH, BG_HEIGHT);
    m_bgPosX = 0.0f;
    m_runSpeed = 4.0f;

    //  Set Player Sprites
    m_playerImg = new ImageKomastar;
    m_playerImg->Setup("images/sprites-player.bmp", 864, 280, true, MAGENTA_COLOR);
    m_player.m_pImg = m_playerImg;
    m_player.Start();
    m_player.SetLifeCount(10);
    
    m_heartImg = new ImageKomastar;
    m_heartImg->Setup("images/heart.bmp", 100, 100, true, MAGENTA_COLOR);

    //  Set Item sprites
    m_scoreItemImg = new ImageKomastar;
    m_magnetItemImg = new ImageKomastar;
    m_immortalItemImg = new ImageKomastar;
    m_giantItemImg = new ImageKomastar;

    m_scoreItemImg->Setup("images/sprites-item-score.bmp", 400, 50, true, MAGENTA_COLOR);
    m_magnetItemImg->Setup("images/sprites-item-magnet.bmp", 400, 50, true, MAGENTA_COLOR);
    m_immortalItemImg->Setup("images/sprites-item-immortal.bmp", 400, 50, true, MAGENTA_COLOR);
    m_giantItemImg->Setup("images/sprites-item-giant.bmp", 400, 50, true, MAGENTA_COLOR);

    m_scoreItemImg->SetupForSprites(8, 0, 50, 50, 5);
    m_magnetItemImg->SetupForSprites(8, 0, 50, 50, 5);
    m_immortalItemImg->SetupForSprites(8, 0, 50, 50, 5);
    m_giantItemImg->SetupForSprites(8, 0, 50, 50, 5);

    m_vecSpritesImgs.push_back(m_playerImg);
    m_vecSpritesImgs.push_back(m_scoreItemImg);
    m_vecSpritesImgs.push_back(m_magnetItemImg);
    m_vecSpritesImgs.push_back(m_immortalItemImg);
    m_vecSpritesImgs.push_back(m_giantItemImg);

    m_player.m_vecObstacles = &m_vecObstacles;
    m_player.m_vecItems = &m_vecItems;
}

void MainGame::Update()
{
    GameNode::Update();
    SpritesRefresh();
    switch (m_currGameState)
    {
    case GAME_READY:
        break;
    case GAME_PLAYING:
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
        break;
    }

    if (m_player.GetLifeCount() < 0)
    {
        m_currGameState = GAME_OVER;
        return;
    }

    m_bgPosX -= m_runSpeed;
    if (m_bgPosX < -BG_WIDTH)
    {
        m_bgPosX = 0.0f;
    }

    m_player.Update();

    m_obsGenDelayCount++;
    if (m_obsGenDelayCount > OBS_GEN_DELAY)
    {
        GenerateObstacle();
        m_obsGenDelayCount = 0;
    }

    m_itemGenDelayCount++;
    if (m_itemGenDelayCount > ITEM_GEN_DELAY)
    {
        GenerateItem();
        m_itemGenDelayCount = 0;
    }

    for (auto obstacleUpdateIter = m_vecObstacles.begin(); obstacleUpdateIter != m_vecObstacles.end(); obstacleUpdateIter++)
    {
        if (obstacleUpdateIter->GetLifeCount() > 0)
        {
            obstacleUpdateIter->SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
        }
        obstacleUpdateIter->Update();
    }

    for (auto itemUpdateIter = m_vecItems.begin(); itemUpdateIter != m_vecItems.end(); itemUpdateIter++)
    {
        if (m_player.GetPlayerBuff() == ITEM_MAGNET)
        {

        }
        else
        {
            itemUpdateIter->SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
        }
        
        itemUpdateIter->Update();
    }

    for (auto itemUpdateIter = m_vecItems.begin(); itemUpdateIter != m_vecItems.end();)
    {
        if (itemUpdateIter->GetLifeCount() <= 0)
        {
            itemUpdateIter = m_vecItems.erase(itemUpdateIter);
        }
        else
        {
            itemUpdateIter++;
        }
    }

    if (g_pKeyManager->isStayKeyDown(VK_SPACE))
    {
        UnitPos pPos = m_player.GetPosition();
        pPos.y -= 5.0f;
        m_player.SetPosition(pPos);
    }

    if (g_pKeyManager->isOnceKeyDown(VK_UP))
    {
        m_runSpeed += 0.5f;
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
    {
        m_runSpeed -= 0.25f;
    }
}

void MainGame::Render()
{
    if (m_player.GetLifeCount() < 0)
    {
        return;
    }
    PatBlt(g_hDC, 0, 0, W_WIDTH, W_HEIGHT, WHITENESS);
    //  Draw BG
    m_bgImg->Render(g_hDC, (int)m_bgPosX, W_HEIGHT - BG_HEIGHT);
    //  Next BG
    m_bgImg->Render(g_hDC, (int)m_bgPosX + BG_WIDTH, W_HEIGHT - BG_HEIGHT);
    m_player.Render();

    for (auto obstacleRenderIter = m_vecObstacles.begin(); obstacleRenderIter != m_vecObstacles.end(); obstacleRenderIter++)
    {
        obstacleRenderIter->Render();
    }

    for (auto itemRenderIter = m_vecItems.begin(); itemRenderIter != m_vecItems.end(); itemRenderIter++)
    {
        itemRenderIter->Render();
    }

    E_ITEM_TYPE itemType = m_player.GetPlayerBuff();
    RECT buffIcon = m_player.m_rtBody;
    buffIcon.left -= 25;
    buffIcon.top -= 25;
    buffIcon.right = buffIcon.left + 25;
    buffIcon.bottom = buffIcon.top + 25;
    switch (itemType)
    {
    case ITEM_IMMORTAL:
        m_immortalItemImg->SpritesRender(g_hDC, buffIcon, 255);
        break;
    case ITEM_MAGNET:
        m_magnetItemImg->SpritesRender(g_hDC, buffIcon, 255);
        break;
    case ITEM_GIANT:
        m_giantItemImg->SpritesRender(g_hDC, buffIcon, 255);
        break;
    }
    
    //  HEALTH BAR
    for (int i = 0; i < m_player.GetLifeCount(); i++)
    {
        m_heartImg->Render(g_hDC, 100 + (100 * i), 10);
    }
#ifdef _DEBUG
    char infoMsg[100];
    sprintf_s(infoMsg, "SPEED : %f  / BG_POS : %f / Life : %d / Buff Timer : %d", m_runSpeed, m_bgPosX, m_player.GetLifeCount(), m_player.m_buffTimer);
    TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
}

void MainGame::GenerateObstacle()
{
    Obstacle tObstacle;
    int objWidth = 50;
    int objHeight = (rand() % 200) + 50;

    tObstacle.SetSize(UnitSize{ objWidth, objHeight });
    tObstacle.SetPosition(UnitPos{ W_WIDTH, W_HEIGHT - (double)objHeight });
    tObstacle.SetBodyRect(tObstacle.GetPosition(), tObstacle.GetSize());
    tObstacle.SetMoveSpeed(UnitSpeed{ -m_runSpeed , 0.0f });
    tObstacle.SetLifeCount(1);

    m_vecObstacles.push_back(tObstacle);
}

void MainGame::GenerateItem()
{
    Item tItem;
    E_ITEM_TYPE itemType;
    double itemChance = (rand() % 10001) * 0.01f;
    if (itemChance > 99.0f)
    {
        //  IMMORTAL
        itemType = ITEM_IMMORTAL;
        tItem.SetItemImg(m_immortalItemImg);
    }
    else if (itemChance > 98.0f)
    {
        //  MAGNET
        itemType = ITEM_MAGNET;
        tItem.SetItemImg(m_magnetItemImg);
    }
    else if (itemChance > 95.0f)
    {
        itemType = ITEM_GIANT;
        tItem.SetItemImg(m_giantItemImg);
    }
    else
    {
        //  SCORE
        itemType = ITEM_SCORE;
        tItem.SetItemImg(m_scoreItemImg);
    }

    tItem.SetItemType(itemType);
    tItem.SetSize(UnitSize{ 50, 50 });
    tItem.SetPosition(UnitPos{ (double)W_WIDTH, W_HEIGHT * 0.75f });
    tItem.SetBodyRect(tItem.GetPosition(), tItem.GetSize());
    tItem.SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
    tItem.SetLifeCount(1);
    tItem.Start();

    m_vecItems.push_back(tItem);
}

void MainGame::SpritesRefresh()
{
    for (int i = 0; i < m_vecSpritesImgs.size(); i++)
    {
        m_vecSpritesImgs[i]->Refresh();
    }
}
