#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
    : m_itemGenDelayCount(0)
    , m_obsGenDelayCount(0)
    , m_isShowSlide(false)
    , m_PosX((double)W_WIDTH)
    , m_gameLevel(1)
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
    delete m_landBlockImg;
    delete m_slideTestImg;
}

void MainGame::Start()
{
    m_currGameState = GAME_READY;
    m_countDownRt = { 0, COUNT_DOWN_RECT_MARGIN, W_WIDTH, W_HEIGHT - COUNT_DOWN_RECT_MARGIN };
    //  Set BG
    m_bgImg = new ImageKomastar;
    m_bgImg->Setup("images/bg.bmp", BG_WIDTH, BG_HEIGHT);
    m_bgPosX = 0.0f;
    m_runSpeed = GAME_SPEED;
    m_holeGenLimitCount = 0;
    m_holeBrush = CreateSolidBrush(RGB(0, 0, 0));

    //  Set Player Sprites
    m_playerImg = new ImageKomastar;
    m_playerImg->Setup("images/sprites-player.bmp", 864, PLAYER_HEIGHT, true, MAGENTA_COLOR);
    m_playerImmortalImg = new ImageKomastar;
    m_playerImmortalImg->Setup("images/sprites-player-immortal.bmp", 864, PLAYER_HEIGHT, true, MAGENTA_COLOR);
    m_player.m_pImg = m_playerImg;
    m_player.Start();
    m_player.m_pImg->SetHelper(&m_drawHelper);
    m_player.SetLifeCount(10);
    
    m_heartImg = new ImageKomastar;
    m_heartImg->Setup("images/heart.bmp", 100, 100, true, MAGENTA_COLOR);
    m_heartImg->SetHelper(&m_drawHelper);

    m_splashBgImg = new ImageKomastar;
    m_splashBgImg->Setup("images/hots-logo-bg.bmp", 1600, 900, true, MAGENTA_COLOR);
    m_splashBgImg->SetupForAlphaBlend();

    m_splashBladeImg = new ImageKomastar;
    m_splashBladeImg->Setup("images/hots-logo-blade.bmp", 1600, 900, true, MAGENTA_COLOR);
    m_splashBladeImg->SetupForAlphaBlend();

    m_uiHelper.SetBgImg(m_splashBgImg);
    m_uiHelper.SetBladeImg(m_splashBladeImg);
    //m_uiHelper.SetupSplash();

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
    m_player.m_vecHoles = &m_vecHoles;
}

void MainGame::Update()
{
    GameNode::Update();
    switch (m_currGameState)
    {
    case GAME_READY:
    {
        Reset();
        if (m_gameLevel > 1)
        {
            m_currGameState = GAME_PLAYING;
        }
        break;
    }
    case GAME_PLAYING:
    {
        if (m_isCounting)
        {
            return;
        }
        SpritesRefresh();
        Play();
        PlayerControl();
        break;
    }
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
    {
        ClearScreen("Clear !");
        break;
    }
    case GAME_OVER:
    {
        char tMsg[100];
        sprintf_s(tMsg, "GAME OVER Max Lvl : %d", m_gameLevel);
        ClearScreen(tMsg);
        break;
    }
    }
    SystemControl();
}

void MainGame::Render()
{    
    switch (m_currGameState)
    {
    case GAME_READY:
    {
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
        break;
    }
    case GAME_PLAYING:
    {
        if (m_isCounting)
        {
            m_uiHelper.PaintBlack();
            CountDown();
            return;
        }
        m_uiHelper.PaintWhite();
        if (m_player.GetLifeCount() < 0)
        {
            return;
        }

        //  Draw BG
        m_bgImg->Render(g_hDC, (int)m_bgPosX, W_HEIGHT - BG_HEIGHT);
        //  Next BG
        m_bgImg->Render(g_hDC, (int)m_bgPosX + BG_WIDTH, W_HEIGHT - BG_HEIGHT);

        DrawObstacles();
        DrawItems();
        DrawHoles();
        DrawPlayer();

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
        RECT txtBox = { W_WIDTH - (int)scoreTxt.size() * 25, 30, W_WIDTH, 80 };
        m_drawHelper.DrawTextBox(txtBox, infoMsg, _RGBA{ 0, 0, 0, 0 }, TEXT("Consolas"));

        txtBox.top = txtBox.top + 50;
        txtBox.bottom = txtBox.top + 50;
        sprintf_s(infoMsg, "Level : %d", m_gameLevel);
        scoreTxt = infoMsg;
        m_drawHelper.DrawTextBox(txtBox, infoMsg, _RGBA{ 0, 0, 0, 0 }, TEXT("Consolas"));

        UnitPos endPos = UnitPos{ (double)(W_WIDTH - m_flagImg->GetWidth() - 10), 200.0f };
        UnitPos startPos = UnitPos{ (endPos.x - 300.0f), 200.0f };
        int miniPlayerSize = 50;
        RECT miniPlayer = { (int)(startPos.x + (m_progress * 2.0f) - miniPlayerSize / 2), (int)(startPos.y - miniPlayerSize), 0, 0 };
        miniPlayer.right = miniPlayer.left + miniPlayerSize;
        miniPlayer.bottom = miniPlayer.top + miniPlayerSize;
        m_playerImg->SpritesRender(g_hDC, miniPlayer, 255);
        m_flagImg->Render(g_hDC, (int)endPos.x, (int)endPos.y - m_flagImg->GetHeight());
        m_drawHelper.DrawLine2D(startPos, endPos, 5, _RGBA{ 0, 0, 0, 0 });
#ifdef _DEBUG
        sprintf_s(infoMsg, "SPEED : %f  / BG_POS : %f / Life : %d / Buff Timer : %d", m_runSpeed, m_bgPosX, m_player.GetLifeCount(), m_player.m_buffTimer);
        TextOut(g_hDC, 10, 10, infoMsg, (int)strlen(infoMsg));
        sprintf_s(infoMsg, "PlayerJump : %f / PosX : %f / PosY : %f / Score : %d", m_player.GetMoveSpeed().y, m_player.GetPosition().x, m_player.GetPosition().y, m_player.GetScore());
        TextOut(g_hDC, 10, 30, infoMsg, (int)strlen(infoMsg));
        sprintf_s(infoMsg, "ItemCount : %d / ObsCount : %d / CurrGravity : %f", (int)m_vecObstacles.size(), (int)m_vecItems.size(), m_player.GetMoveSpeed().y);
        TextOut(g_hDC, 10, 50, infoMsg, (int)strlen(infoMsg));
        sprintf_s(infoMsg, "GameTimer : %d / GameLevel : %d", m_gameTimer, m_gameLevel);
        TextOut(g_hDC, 10, 70, infoMsg, (int)strlen(infoMsg));
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

void MainGame::Reset()
{
    m_bgPosX = 0.0f;
    m_bgPosX2 = 0.0f;
    m_progress = 0.0f;
    m_gameTimer = INIT_GAME_TIMER * m_gameLevel;
    m_showTimer = INIT_SHOW_TIMER;
    m_showCount = 0;
    m_runSpeed = GAME_SPEED + (double)m_gameLevel * 0.5f;
    m_isCounting = true;
    m_itemGenDelayCount= 0;
    m_obsGenDelayCount = 0;
    m_holeGenLimitCount = 0;
    m_isShowSlide = false;
    m_PosX = (double)W_WIDTH;

    m_player.Start();
    m_player.Reset();
    m_vecItems.clear();
    m_vecObstacles.clear();
    m_vecHoles.clear();

    m_uiHelper.ResetSlide();
    m_countDownRt = { 0, COUNT_DOWN_RECT_MARGIN, W_WIDTH, W_HEIGHT - COUNT_DOWN_RECT_MARGIN };
}

void MainGame::ShowTimerReset()
{
    m_showTimer = INIT_SHOW_TIMER;
    m_showCount = 0;
}

void MainGame::LoadImages()
{
    m_slideTestImg = new ImageKomastar;
    m_slideTestImg->Setup("images/splash-ana.bmp", 1600, 730, true, MAGENTA_COLOR);
    m_slideTestImg->SetupForAlphaBlend();

    m_landBlockImg = new ImageKomastar;
    m_landBlockImg->Setup("images/sprites-landblock.bmp", 170, 170, true, MAGENTA_COLOR);
    m_landBlockImg->SetupForAlphaBlend();

    m_holeBlockImg = new ImageKomastar;
    m_holeBlockImg->Setup("images/img-holeblock.bmp", 200, 200, true, MAGENTA_COLOR);
    m_holeBlockImg->SetupForAlphaBlend();

    m_bkBg = new ImageKomastar;
    m_bkBg->Setup("images/blackBg.bmp", 1920, 1080, true, MAGENTA_COLOR);
    m_bkBg->SetupForAlphaBlend();

    m_flagImg = new ImageKomastar;
    m_flagImg->Setup("images/img-flag.bmp", 25, 50, true, MAGENTA_COLOR);
    m_flagImg->SetupForAlphaBlend();
}

void MainGame::Play()
{
    m_gameTimer--;
    m_progress = (double)((INIT_GAME_TIMER * m_gameLevel) - m_gameTimer) / (double)(INIT_GAME_TIMER * m_gameLevel);
    m_progress *= 100.0f;
    if (m_gameTimer < 0)
    {
        m_gameLevel++;
        m_gameTimer = INIT_GAME_TIMER * m_gameLevel;
        m_currGameState = GAME_CLEAR;
        return;
    }

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

    m_obsGenDelayCount += (int)(m_runSpeed * 0.2f);
    if (m_obsGenDelayCount > OBS_GEN_DELAY)
    {
        GenerateObstacle();
        m_obsGenDelayCount = 0;
    }

    m_itemGenDelayCount += (int)(m_runSpeed * 0.2f);
    if (m_itemGenDelayCount > ITEM_GEN_DELAY)
    {
        GenerateItem();
        m_itemGenDelayCount = 0;
    }

    m_holeGenLimitCount += (int)(m_runSpeed * 0.2f);
    if (m_holeGenLimitCount > HOLE_GEN_LIMITER)
    {
        GenerateHole();
        m_holeGenLimitCount = 0;
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
                itemHeightOffset += 100.0f;
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

    for (auto holeUpdateIter = m_vecHoles.begin(); holeUpdateIter != m_vecHoles.end(); holeUpdateIter++)
    {
        holeUpdateIter->Update();
        if (holeUpdateIter->GetPosition().x < 0 - holeUpdateIter->GetSize().w)
        {
            holeUpdateIter->SetLifeCount(0);
        }
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

    for (auto holeEraseIter = m_vecHoles.begin(); holeEraseIter != m_vecHoles.end();)
    {
        if (holeEraseIter->GetLifeCount() <= 0)
        {
            holeEraseIter = m_vecHoles.erase(holeEraseIter);
        }
        else
        {
            holeEraseIter++;
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

void MainGame::DrawHoles()
{
    for (auto iter = m_vecHoles.begin(); iter != m_vecHoles.end(); iter++)
    {
        iter->Render();
    }
}

void MainGame::GenerateObstacle()
{
    Obstacle tObstacle;
    int objWidth = 50;
    int objHeight = (rand() % 200) + 50;

    tObstacle.SetSize(UnitSize{ objWidth, objHeight });
    tObstacle.SetPosition(UnitPos{ W_WIDTH + OBJ_GEN_OFFSET, (W_HEIGHT - FLOOR) - (double)objHeight * 0.5f });
    tObstacle.SetBodyRect(tObstacle.GetPosition(), tObstacle.GetSize());
    tObstacle.SetMoveSpeed(UnitSpeed{ -m_runSpeed , 0.0f });
    tObstacle.SetLifeCount(1);
    tObstacle.m_pImg = m_landBlockImg;
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
    tItem.SetPosition(UnitPos{ (double)W_WIDTH + OBJ_GEN_OFFSET, FLOOR_POS_Y - 100.0f });
    tItem.SetBodyRect(tItem.GetPosition(), tItem.GetSize());
    tItem.SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
    tItem.SetLifeCount(1);
    tItem.Start();
    tItem.Activate();

    m_vecItems.push_back(tItem);
}

void MainGame::GenerateHole()
{
    Hole tHole;
    tHole.SetPosition(UnitPos{ (double)(W_WIDTH + tHole.GetSize().w), (double)(W_HEIGHT - (tHole.GetSize().h * 0.5f)) });
    tHole.SetBodyRect(tHole.GetPosition(), tHole.GetSize());
    tHole.SetMoveSpeed(UnitSpeed{ -m_runSpeed, 0.0f });
    tHole.SetLifeCount(1);
    tHole.SetImg(m_holeBlockImg);
    tHole.SetBrush(&m_holeBrush);

    m_vecHoles.push_back(tHole);
}

void MainGame::SpritesRefresh()
{
    for (int i = 0; i < m_vecSpritesImgs.size(); i++)
    {
        m_vecSpritesImgs[i]->Refresh();
    }
}

void MainGame::CountDown()
{
    if (m_showCount == 0)
    {
        m_showCount++;
        m_showTimer = INIT_SHOW_TIMER;
    }
    else if (m_showCount > INIT_COUNT_DOWN)
    {
        m_isCounting = false;
        return;
    }

    m_showTimer--;
    if (m_showTimer < 0)
    {
        m_showCount++;
        m_countDownRt = { 0, COUNT_DOWN_RECT_MARGIN, W_WIDTH, W_HEIGHT - COUNT_DOWN_RECT_MARGIN };
        m_showTimer = INIT_SHOW_TIMER;
    }

    int step = 50;
    m_countDownRt.left -= step;
    m_countDownRt.right += step;
    m_countDownRt.top -= step;
    m_countDownRt.bottom += step;
    char countMsg[100];
    string szCount = "";
    sprintf_s(countMsg, "%d", (INIT_COUNT_DOWN + 1) - m_showCount);
    szCount = countMsg;
    m_drawHelper.DrawTextBox(m_countDownRt, szCount, _RGBA{ 150, 0, 0, 0 }, TEXT("Consolas"));
}

void MainGame::ClearScreen(string szText)
{
    m_uiHelper.SlideScreen(m_bkBg, 10.0f, 2, true, 100.0f);
    if (m_showCount < 3)
    {
        m_showTimer--;
    }
    if (m_showTimer < 0)
    {
        m_showCount++;
        m_showTimer = INIT_SHOW_TIMER;
    }

    RECT rt = { 0, (int)(W_HEIGHT * 0.4f), W_WIDTH, (int)(W_HEIGHT * 0.5f) };
    string scoreTxt = szText;
     if (m_showCount >= 1)
    {
        m_drawHelper.DrawTextBox(rt, scoreTxt, _RGBA{ 120, 120, 120, 0 }, TEXT("Consolas"));
    }
    
    if(m_showCount >= 2)
    {
        rt = { 0, (int)(W_HEIGHT * 0.5f), W_WIDTH, (int)(W_HEIGHT * 0.6f) };
        char infoMsg[100];
        sprintf_s(infoMsg, "SCORE : %d", m_player.GetScore());
        scoreTxt = infoMsg;
        m_drawHelper.DrawTextBox(rt, scoreTxt, _RGBA{ 200, 200, 200, 0 }, TEXT("Consolas"));
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
            m_currGameState = GAME_PAUSE;
            break;
        case GAME_PAUSE:
            m_currGameState = GAME_PLAYING;
            break;
        case GAME_CLEAR:
        {
            if (m_showCount < 2)
            {

            }
            else
            {
                m_currGameState = GAME_READY;
            }
            break;
        }
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

    if (g_pKeyManager->isOnceKeyDown('Q'))
    {
        m_player.CastQSkill();
    }
}
