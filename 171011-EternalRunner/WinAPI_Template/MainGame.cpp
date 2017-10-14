#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame() :
    m_itemGenDelayCount(0),
    m_obsGenDelayCount(0),
    m_isShowSlide(false),
    m_PosX((double)W_WIDTH)
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
    m_runSpeed = GAME_SPEED;

    //  Set Player Sprites
    m_playerImg = new ImageKomastar;
    m_playerImg->Setup("images/sprites-player.bmp", 864, 280, true, MAGENTA_COLOR);
    m_player.m_pImg = m_playerImg;
    m_player.Start();
    m_player.m_pImg->SetHelper(&m_drawHelper);
    m_player.SetLifeCount(10);
    
    m_heartImg = new ImageKomastar;
    m_heartImg->Setup("images/heart.bmp", 100, 100, true, MAGENTA_COLOR);
    m_heartImg->SetHelper(&m_drawHelper);

    m_splashImg = new ImageKomastar;
    m_splashImg->Setup("images/bg-frozenthrone.bmp", 2113, 900, true, MAGENTA_COLOR);
    m_splashImg->SetupForAlphaBlend();
    m_uiHelper.SetImg(m_splashImg);

    //  Set Item sprites
    m_scoreItemImg = new ImageKomastar;
    m_magnetItemImg = new ImageKomastar;
    m_immortalItemImg = new ImageKomastar;
    m_giantItemImg = new ImageKomastar;

    m_scoreItemImg->Setup("images/sprites-item-score.bmp", 400, 50, true, MAGENTA_COLOR);
    m_magnetItemImg->Setup("images/sprites-item-magnet.bmp", 400, 50, true, MAGENTA_COLOR);
    m_immortalItemImg->Setup("images/sprites-item-immortal.bmp", 400, 50, true, MAGENTA_COLOR);
    m_giantItemImg->Setup("images/sprites-item-giant.bmp", 400, 50, true, MAGENTA_COLOR);

    m_scoreItemImg->SetHelper(&m_drawHelper);
    m_magnetItemImg->SetHelper(&m_drawHelper);
    m_immortalItemImg->SetHelper(&m_drawHelper);
    m_giantItemImg->SetHelper(&m_drawHelper);

    LoadImages();

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
    switch (m_currGameState)
    {
    case GAME_READY:
        break;
    case GAME_PLAYING:
    {
        SpritesRefresh();
        Play();
        PlayerControl();
        break;
    }
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
        break;
    }
    SystemControl();
}

void MainGame::Render()
{    
    switch (m_currGameState)
    {
    case GAME_READY:
    {
        m_uiHelper.PaintBlack();
        m_uiHelper.SetGameState(m_currGameState);
        if (m_isShowSlide)
        {
            m_uiHelper.SlideScreen(m_slideTestImg, 25.0f, 2, true, 10.0f);
        }
        else
        {
            m_uiHelper.ResetSlide();
            m_uiHelper.Render();
        }
        m_numberTestImg->SpritesRender(g_hDC, RECT{ 100, 100, 200, 200 }, 255);
        m_numberTestImg->Refresh();
        break;
    }
    case GAME_PLAYING:
    {
        m_uiHelper.PaintWhite();
        if (m_player.GetLifeCount() < 0)
        {
            return;
        }

        //  Draw BG
        m_bgImg->Render(g_hDC, (int)m_bgPosX, W_HEIGHT - BG_HEIGHT);
        //  Next BG
        m_bgImg->Render(g_hDC, (int)m_bgPosX + BG_WIDTH, W_HEIGHT - BG_HEIGHT);

        DrawPlayer();
        DrawObstacles();
        DrawItems();

        E_ITEM_TYPE itemType = m_player.GetPlayerBuff();
        RECT buffIcon = m_player.m_rtBody;
        buffIcon.left -= 50;
        buffIcon.top -= 50;
        buffIcon.right = buffIcon.left + 50;
        buffIcon.bottom = buffIcon.top + 50;
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

        char infoMsg[100];
        sprintf_s(infoMsg, "SCORE : %d", m_player.GetScore());

        string scoreTxt = infoMsg;
        RECT txtBox = { W_WIDTH - scoreTxt.size() * 25, 30, W_WIDTH, 80 };
        m_drawHelper.DrawTextBox(txtBox, infoMsg, _RGBA{ 0, 0, 0, 0 }, TEXT("Consolas"));
#ifdef _DEBUG
        sprintf_s(infoMsg, "SPEED : %f  / BG_POS : %f / Life : %d / Buff Timer : %d", m_runSpeed, m_bgPosX, m_player.GetLifeCount(), m_player.m_buffTimer);
        TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
        sprintf_s(infoMsg, "PlayerJump : %f / PosX : %f / PosY : %f / Score : %d", m_player.GetMoveSpeed().y, m_player.GetPosition().x, m_player.GetPosition().y, m_player.GetScore());
        TextOut(g_hDC, 10, 30, infoMsg, (int)strlen(infoMsg));
        sprintf_s(infoMsg, "ItemCount : %d / ObsCount : %d", m_vecObstacles.size(), m_vecItems.size());
        TextOut(g_hDC, 10, 50, infoMsg, (int)strlen(infoMsg));
#endif // _DEBUG
        break;
    }
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
        break;
    default:
        break;
    }
}

void MainGame::LoadImages()
{
    m_slideTestImg = new ImageKomastar;
    m_slideTestImg->Setup("images/splash-ana.bmp", 1600, 730, true, MAGENTA_COLOR);
    m_slideTestImg->SetupForAlphaBlend();

    m_numberTestImg = new ImageKomastar;
    m_numberTestImg->Setup("images/sprites-number.bmp", 500, 40, true, MAGENTA_COLOR);
    m_numberTestImg->SetupForAlphaBlend();
    m_numberTestImg->SetupForSprites(10, 1, 50, 40, 1);

}

void MainGame::Play()
{
    if (m_player.GetLifeCount() < 1)
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

    m_obsGenDelayCount += (int)m_runSpeed * 0.2;
    if (m_obsGenDelayCount > OBS_GEN_DELAY)
    {
        GenerateObstacle();
        m_obsGenDelayCount = 0;
    }

    m_itemGenDelayCount += m_runSpeed * 0.2;
    if (m_itemGenDelayCount > ITEM_GEN_DELAY)
    {
        GenerateItem();
        m_itemGenDelayCount = 0;
    }



    for (auto obstacleUpdateIter = m_vecObstacles.begin(); obstacleUpdateIter != m_vecObstacles.end(); obstacleUpdateIter++)
    {
        if (obstacleUpdateIter->GetLifeCount() > 0 && obstacleUpdateIter->GetMovable())
        {
            obstacleUpdateIter->SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
        }

        if (obstacleUpdateIter->GetPosition().x < -200.0f)
        {
            obstacleUpdateIter->SetLifeCount(0);
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
            for (auto iter = m_vecObstacles.begin(); iter != m_vecObstacles.end(); iter++)
            {
                double distance = m_geoHelper.GetDistance(itemUpdateIter->GetPosition(), iter->GetPosition());
                double obsHeight = iter->GetSize().h;
                double itemHeightOffset = obsHeight - distance;
                itemHeightOffset += 30.0f;
                if (distance < obsHeight)
                {
                    if (itemUpdateIter->GetPosition().x > W_WIDTH)
                    {
                        itemUpdateIter->SetPosition(UnitPos{ itemUpdateIter->GetPosition().x, FLOOR_POS_Y - itemHeightOffset });
                    }
                }
            }
            itemUpdateIter->SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
        }

        if (itemUpdateIter->GetPosition().x < -200.0f)
        {
            itemUpdateIter->SetLifeCount(0);
        }
        itemUpdateIter->Update();
    }

    for (auto obsEraseIter = m_vecObstacles.begin(); obsEraseIter != m_vecObstacles.end();)
    {
        if (obsEraseIter->GetLifeCount() <= 0)
        {
            obsEraseIter = m_vecObstacles.erase(obsEraseIter);
        }
        else
        {
            obsEraseIter++;
        }
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
}

void MainGame::DrawPlayer()
{
    m_player.Render();
}

void MainGame::DrawObstacles()
{
    for (auto obstacleRenderIter = m_vecObstacles.begin(); obstacleRenderIter != m_vecObstacles.end(); obstacleRenderIter++)
    {
        obstacleRenderIter->Render();
    }
}

void MainGame::DrawItems()
{
    for (auto itemRenderIter = m_vecItems.begin(); itemRenderIter != m_vecItems.end(); itemRenderIter++)
    {
        itemRenderIter->Render();
    }
}

void MainGame::GenerateObstacle()
{
    Obstacle tObstacle;
    int objWidth = 50;
    int objHeight = (rand() % 200) + 50;

    tObstacle.SetSize(UnitSize{ objWidth, objHeight });
    tObstacle.SetPosition(UnitPos{ W_WIDTH + OBJ_GEN_OFFSET, W_HEIGHT - (double)objHeight });
    tObstacle.SetBodyRect(tObstacle.GetPosition(), tObstacle.GetSize());
    tObstacle.SetMoveSpeed(UnitSpeed{ -m_runSpeed , 0.0f });
    tObstacle.SetLifeCount(1);
    tObstacle.Activate();

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
    else if (itemChance > 90.0f)
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
    tItem.SetPosition(UnitPos{ (double)W_WIDTH + OBJ_GEN_OFFSET, FLOOR_POS_Y });
    tItem.SetBodyRect(tItem.GetPosition(), tItem.GetSize());
    tItem.SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
    tItem.SetLifeCount(1);
    tItem.Start();
    tItem.Activate();

    m_vecItems.push_back(tItem);
}

void MainGame::SpritesRefresh()
{
    for (int i = 0; i < m_vecSpritesImgs.size(); i++)
    {
        m_vecSpritesImgs[i]->Refresh();
    }
}

void MainGame::SystemControl()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
    {
        m_isShowSlide = !m_isShowSlide;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_UP))
    {
        m_runSpeed += 0.5f;
    }
    else if (g_pKeyManager->isOnceKeyDown(VK_DOWN))
    {
        m_runSpeed -= 0.25f;
    }

    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        switch (m_currGameState)
        {
        case GAME_READY:
            m_currGameState = GAME_PLAYING;
            break;
        case GAME_PLAYING:
            break;
        case GAME_PAUSE:
            break;
        case GAME_CLEAR:
            break;
        case GAME_OVER:
            break;
        default:
            break;
        }
    }
}

void MainGame::PlayerControl()
{
    if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
    {
        if (m_player.GetPlayerState() == PLAYER_RUN)
        {
            m_player.SetPlayerState(PLAYER_JUMP);
            m_player.m_moveSpeed.y = -20.0f;
        }
        else if (m_player.GetPlayerState() == PLAYER_JUMP)
        {
            m_player.SetPlayerState(PLAYER_DJUMP);
            m_player.m_moveSpeed.y = -20.0f;
        }
    }
}
