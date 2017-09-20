#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
    m_gameLevel = 1;
    m_isSetup = false;
    m_itemChance = 0.85f;
    m_antiMisfortune = 0.0f;
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
        if (m_isSetup == false)
        {
            SetupGame(m_gameLevel);
        }
        break;
    case GAME_PLAYING:
    {
        PlayGame();
        m_ball.Update();
        m_player.Update();
        for (auto blockUpdateIter = m_vecItemBlock.begin(); blockUpdateIter != m_vecItemBlock.end(); blockUpdateIter++)
        {
            blockUpdateIter->Move();
        }
        break;
        IsEnd();
    }
    case GAME_PAUSE:
        break;
    case GAME_CLEAR:
        break;
    case GAME_OVER:
        m_isSetup = false;
        if (m_isSetup == false)
        {
            SetupGame(m_gameLevel);
        }
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

    for (auto itemRenderIter = m_vecItemBlock.begin(); itemRenderIter != m_vecItemBlock.end(); itemRenderIter++)
    {
        itemRenderIter->Render();
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
            m_isSetup = false;
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
    m_isSetup = true;
}

void MainGame::SetupPlayer()
{
    m_player.SetPosition(m_ptPlayerPos);
}

void MainGame::SetupBall()
{
    NumberGenerator numGen;
    UnitPos ptBallPos = { m_ptPlayerPos.x, m_ptPlayerPos.y - 100.0f };
    UnitSpeed ballSpeed;
    ballSpeed.x = numGen.GetRandomNumber(6, 7, false) * 1.0f;
    ballSpeed.y = numGen.GetRandomNumber(6, 7, true) * 1.0f;
    m_ball.SetPosition(ptBallPos);
    m_ball.SetMoveDir(ballSpeed);
}

void MainGame::SetBlock(int LifeCount)
{
    m_vecBlock.clear();
    m_vecItemBlock.clear();
    int marginX = 100;
    int marginY = 200;
    for (int rowCount = 0; rowCount < BLOCK_ROW; rowCount++)
    {
        for (int colCount = 0; colCount < BLOCK_COL; colCount++)
        {
            Block block;
            UnitPos ptSpawn = { marginX + (BLOCK_WIDTH + 5) * colCount, marginY + (BLOCK_HEIGHT + 5) * rowCount };
            block.SetPosition(ptSpawn);
            block.m_LifeCount = LifeCount;
            m_vecBlock.push_back(block);
        }
    }
}

void MainGame::PlayGame()
{
    //  Ball 은 화면 밖으로 나갈 수 없다.
    E_EDGE collEdge = m_gameMap.IsInsideWindow(*m_ball.GetBodyRect());
    switch (collEdge)
    {
    case LEFT_EDGE:
        m_ball.SetMoveDirReverse(REVERSE_X);
        m_ball.m_ptMoveDir.x *= 0.9f;
        break;
    case RIGHT_EDGE:
        m_ball.SetMoveDirReverse(REVERSE_X);
        m_ball.m_ptMoveDir.x *= 0.9f;
        break;
    case TOP_EDGE:
        m_ball.SetMoveDirReverse(REVERSE_Y);
        m_ball.m_ptMoveDir.y *= 0.9f;
        break;
    case BOTTOM_EDGE:
        m_currGameState = GAME_OVER;
        break;
    case END_EDGE:
        break;
    default:
        break;
    }

    BallPlayerCollision();

    //  Ball - Block 충돌
    for (auto blockCollIter = m_vecBlock.begin(); blockCollIter != m_vecBlock.end(); blockCollIter++)
    {
        E_REFLECT_DIR dir = m_physics.BlockCollider(m_ball.m_rtBody, blockCollIter->m_rtBody);
        if (dir != REVERSE_END)
        {
            m_ball.SetMoveDirReverse(dir);
            m_ball.m_ptMoveDir.x *= 1.08;
            m_ball.m_ptMoveDir.y *= 1.08;
            blockCollIter->m_LifeCount -= 1;

            if (RollingDice() > m_itemChance)
            {
                //  GET ITEM
                m_antiMisfortune = 0.0f;
                Block itemBlock;
                UnitPos ptSpawn = blockCollIter->GetPosition();
                itemBlock.SetPosition(ptSpawn);
                itemBlock.m_LifeCount = 1;
                itemBlock.m_ptMoveDir = UnitSpeed{ 0.0f, 5.0f };
                itemBlock.SetColor(0, 0, 0);
                m_vecItemBlock.push_back(itemBlock);
                break;
            }
            else
            {
                AntiMisfortune();
            }
            break;
        }
    }

    //  Item - Player 충돌
    for (auto itemCollIter = m_vecItemBlock.begin(); itemCollIter != m_vecItemBlock.end();)
    {
        if (PlayerBlockCollision(*itemCollIter))
        {
            itemCollIter = m_vecItemBlock.erase(itemCollIter);
            if (m_player.m_rtBody.right - m_player.m_rtBody.left < 600)
            {
                m_player.m_rtBody.left -= 25;
                m_player.m_rtBody.right += 25;
            }
            break;
        }
        else
        {
            itemCollIter++;
        }
    }

    Refresh();
}

void MainGame::IsEnd()
{
    if (m_vecBlock.size() <= 0)
    {
        m_currGameState = GAME_CLEAR;
    }
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

double MainGame::RollingDice()
{
    NumberGenerator numGen;
    double chance = numGen.GetRandomNumber(100, false) * 0.01;

    return chance + m_antiMisfortune;
}

void MainGame::AntiMisfortune()
{
    m_antiMisfortune += 0.05f;
    if (m_antiMisfortune > 0.9f)
    {
        m_antiMisfortune = 0.9f;
    }
}

void MainGame::BallPlayerCollision()
{
    //  Ball - Player 충돌
    UnitPos ballPos = m_ball.GetPosition();
    UnitPos playerPos = m_player.GetPosition();

    RECT rt;
    bool bpCollision = IntersectRect(&rt, &m_player.m_rtBody, &m_ball.m_rtBody);

    if (bpCollision)
    {
        if (m_player.m_rtBody.left <= ballPos.x &&
            ballPos.x <= m_player.m_rtBody.right)
        {
            //  상단 충돌
            m_ball.m_ptMoveDir.x = m_player.m_ptMoveDir.x + m_ball.m_ptMoveDir.x;
            m_ball.m_ptMoveDir.y = -m_ball.m_ptMoveDir.y;
        }
        else if ((ballPos.x < m_player.m_rtBody.left &&
            m_player.m_rtBody.top < ballPos.y) ||
            (ballPos.x > m_player.m_rtBody.right &&
                ballPos.y > m_player.m_rtBody.top))
        {
            //  좌상단or우상단 충돌
            m_ball.SetMoveDirReverse(REVERSE_ALL);
        }
        else if (ballPos.y <= m_player.m_rtBody.top &&
            ballPos.y >= m_player.m_rtBody.bottom)
        {
            //  측면 충돌
            m_ball.m_ptMoveDir.x = m_player.m_ptMoveDir.x - m_ball.m_ptMoveDir.x;
        }
    }
}

E_REFLECT_DIR MainGame::BallBlockCollision(Block BlockRect)
{
    //  Ball - Player 충돌
    UnitPos ballPos = m_ball.GetPosition();

    RECT rt;
    bool bpCollision = IntersectRect(&rt, &BlockRect.m_rtBody, &m_ball.m_rtBody);

    if (bpCollision)
    {
        if (BlockRect.m_rtBody.left <= ballPos.x &&
            ballPos.x <= BlockRect.m_rtBody.right)
        {
            //  상하단 충돌
            m_ball.m_ptMoveDir.x = BlockRect.m_ptMoveDir.x + m_ball.m_ptMoveDir.x;
            m_ball.m_ptMoveDir.y = -m_ball.m_ptMoveDir.y;
            return REVERSE_Y;
        }
        else if ((ballPos.x < BlockRect.m_rtBody.left &&
            BlockRect.m_rtBody.top < ballPos.y) ||
            (ballPos.x > BlockRect.m_rtBody.right &&
                ballPos.y > BlockRect.m_rtBody.top))
        {
            //  좌상단or우상단 충돌
            m_ball.SetMoveDirReverse(REVERSE_ALL);
            return REVERSE_ALL;
        }
        else if (ballPos.y <= BlockRect.m_rtBody.top &&
            ballPos.y >= BlockRect.m_rtBody.bottom)
        {
            //  측면 충돌
            m_ball.m_ptMoveDir.x = BlockRect.m_ptMoveDir.x - m_ball.m_ptMoveDir.x;
            return REVERSE_X;
        }
    }
    else
    {
        return REVERSE_END;
    }
}

bool MainGame::PlayerBlockCollision(Block BlockRect)
{
    //  Item - Player 충돌
    RECT rt;
    bool ItemCollision = false;

    ItemCollision = IntersectRect(&rt, &m_player.m_rtBody, &BlockRect.m_rtBody);
    if (ItemCollision)
    {
        return true;
    }
    return false;
}
