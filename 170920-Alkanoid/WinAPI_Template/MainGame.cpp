#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_gameLevel = 1;
    Start();
}


MainGame::~MainGame()
{
}

void MainGame::Start()
{
    SetupGame(m_gameLevel);
}

void MainGame::Update()
{
    GameNode::Update();

    SystemControl();
    PlayerControl();

    switch (m_currGameState)
    {
    case GAME_READY:
        break;
    case GAME_PLAYING:
        PlayGame();
        m_ball.Update();
        m_player.Update();
        break;
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
        break;
    case GAME_END:
        break;
    default:
        break;
    }
}

void MainGame::Render()
{
    m_player.Render();
    m_ball.Render();
    for (auto blockRenderIter = m_vecBlock.begin(); blockRenderIter != m_vecBlock.end(); blockRenderIter++)
    {
        blockRenderIter->Render();
    }
}

void MainGame::SystemControl()
{
    if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
    {
        switch (m_currGameState)
        {
        case GAME_READY:
        case GAME_PAUSE:
        case GAME_CLEAR:
            m_currGameState = GAME_PLAYING;
            break;
        case GAME_PLAYING:
            m_currGameState = GAME_PAUSE;
            break;
        case GAME_OVER:
            m_currGameState = GAME_READY;
            break;
        }
    }
}

void MainGame::PlayerControl()
{
    if (g_pKeyManager->isStayKeyDown(VK_LEFT))
    {
        //  Player move left
        m_player.SetMoveDir(UnitSpeed{ -PLAYER_SPEED, 0 });
    }
    else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
    {
        //  Player move right
        m_player.SetMoveDir(UnitSpeed{ PLAYER_SPEED, 0 });
    }
    else
    {
        m_player.Stop();
    }
}

void MainGame::SetupGame(int Level)
{
    SetupPlayer();
    SetupBall();
    SetBlock(Level);
    m_currGameState = GAME_READY;
}

void MainGame::SetupPlayer()
{
    m_player.SetPosition(m_ptPlayerPos);
}

void MainGame::SetupBall()
{
    NumberGenerator numGen;
    POINT ptBallPos = { m_ptPlayerPos.x, m_ptPlayerPos.y - 100 };
    UnitSpeed ballSpeed;
    ballSpeed.x = numGen.GetRandomNumber(6, 7, false) * 1.0f;
    ballSpeed.y = numGen.GetRandomNumber(6, 7, true) * 1.0f;
    m_ball.SetPosition(ptBallPos);
    m_ball.SetMoveDir(ballSpeed);
}

void MainGame::SetBlock(int LifeCount)
{
    int marginX = 100;
    int marginY = 200;
    for (int rowCount = 0; rowCount < BLOCK_ROW; rowCount++)
    {
        for (int colCount = 0; colCount < BLOCK_COL; colCount++)
        {
            Block block;
            POINT ptSpawn = { marginX + (BLOCK_WIDTH + 5) * colCount, marginY + (BLOCK_HEIGHT + 5) * rowCount };
            block.SetPosition(ptSpawn);
            block.m_LifeCount = LifeCount;
            m_vecBlock.push_back(block);
        }
    }
}

void MainGame::PlayGame()
{
    //  Ball Collision Check
    E_EDGE collEdge = m_gameMap.IsInsideWindow(m_ball.GetBodyRect());
    UnitSpeed ballSpeed = m_ball.GetMoveDir();
    switch (collEdge)
    {
    case LEFT_EDGE:
    case RIGHT_EDGE:
        ballSpeed.x = -ballSpeed.x;
        break;
    case TOP_EDGE:
    case BOTTOM_EDGE:
        ballSpeed.y = -ballSpeed.y;
        break;
    }
    m_ball.SetMoveDir(ballSpeed);

    for (auto blockCollIter = m_vecBlock.begin(); blockCollIter != m_vecBlock.end(); blockCollIter++)
    {
        bool isCollision = false;
        isCollision = m_gameMap.IsCollision(&blockCollIter->m_rtBody, &m_ball.m_rtBody);
        if (isCollision)
        {
            blockCollIter->m_LifeCount -= 1;
            E_REFLECT_DIR reflectDir = m_physics.BlockCollider(*m_ball.GetBodyRect(), *blockCollIter->GetBodyRect());
            m_ball.SetMoveDirReverse(reflectDir);
        }
    }

    E_REFLECT_DIR pDir = m_physics.BlockCollider(*m_ball.GetBodyRect(), *m_player.GetBodyRect());
    POINT ballPos = m_ball.GetPosition();
    POINT playerPos = m_player.GetPosition();

    
    if (pDir == REVERSE_ALL)
    {
        if (ballPos.x <= playerPos.x || ballPos.x >= playerPos.x)
        {
            pDir = REVERSE_X;
        }
    }
    if (pDir == REVERSE_X)
    {

    }
    else if (pDir == REVERSE_Y)
    {

    }
    m_ball.SetMoveDirReverse(pDir);

    Refresh();
}

void MainGame::Refresh()
{
    for (auto blockEraseIter = m_vecBlock.begin(); blockEraseIter != m_vecBlock.end();)
    {
        if (blockEraseIter->m_LifeCount <= 0)
        {
            blockEraseIter = m_vecBlock.erase(blockEraseIter);
        }
        else
        {
            blockEraseIter++;
        }
    }
}
