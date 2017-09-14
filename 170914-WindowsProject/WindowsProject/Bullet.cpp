#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

int Bullet::GetRemainBullet()
{
    return m_remainBullet;
}

void Bullet::CreateBulletRain(int BulletCount)
{
    m_remainBullet = BulletCount;
    for (int i = 0; i < BulletCount; i++)
    {
        int K = rand();
        srand(time(NULL) * i * K);
        int xPos = rand() % 1200;
        int yPos = rand() % (BulletCount * 3);
        RECT rectBullet;
        rectBullet.left = xPos;
        rectBullet.right = xPos + BULLET_WIDTH;
        rectBullet.top = -yPos;
        rectBullet.bottom = -yPos + BULLET_HEIGHT;

        m_vecBullet.push_back(rectBullet);
    }
}

void Bullet::DropBulletRain(Player* player)
{
    int vecBulletSize = m_vecBullet.size();
    vector<RECT>::iterator iter;
    for (iter = m_vecBullet.begin(); iter != m_vecBullet.end(); /**/)
    {
        RECT playerRect = player->GetPlayerRect();
        int playerTopPosY = playerRect.top;
        int playerBotPosY = playerRect.bottom;
        int bulletBotPosY = iter->bottom;
        int bulletTopPosY = iter->top;

        bool isCollide = false;
        //  총알 바닥면이 플레이어 머리 고도 보다 낮을때
        if (bulletBotPosY > playerTopPosY)
        {
            isCollide = CollisionValidate(playerRect, *iter);
            if (isCollide)  //  충돌 감지!
            {
                player->SetPlayerAliveFlag(!isCollide);
                break;
            }
        }
        else
        {
        }
        iter->top += GRAVITY;
        iter->bottom += GRAVITY;

        if (bulletTopPosY > playerBotPosY)
        {
            //  바닥을 지나간 총알
            m_remainBullet -= 1;
            iter = m_vecBullet.erase(iter);
        }
        else
        {
            iter++;
        }
    }
    /*
    for (int i = 0; i < vecBulletSize; i++)
    {
        RECT playerRect = player->GetPlayerRect();
        int playerTopPosY = playerRect.top;
        int playerBotPosY = playerRect.bottom;
        int bulletBotPosY = m_vecBullet[i].bottom;
        int bulletTopPosY = m_vecBullet[i].top;
        bool isCollide = false;
        if (bulletTopPosY > playerBotPosY)
        {
            //  바닥을 지나간 총알
            m_remainBullet -= 1;
        }
        //  총알 바닥면이 플레이어 머리 고도 보다 낮을때
        else if (bulletBotPosY > playerTopPosY)
        {
            isCollide = CollisionValidate(playerRect, m_vecBullet[i]);
            if (isCollide)  //  충돌 감지!
            {
                player->SetPlayerAliveFlag(!isCollide);
                break;
            }
        }
        m_vecBullet[i].top += GRAVITY;
        m_vecBullet[i].bottom += GRAVITY;
    }
    */
}

void Bullet::DrawBulletRain(HDC hdc)
{
    int vecBulletSize = m_vecBullet.size();
    for (int i = 0; i < vecBulletSize; i++)
    {
        Rectangle(hdc, m_vecBullet[i].left, m_vecBullet[i].top, m_vecBullet[i].right, m_vecBullet[i].bottom);
    }
}

bool Bullet::CollisionValidate(RECT Player, RECT Bullet)
{
    bool retIsCollide = false;

    int playerLeft = Player.left;
    int playerRight = Player.right;
    int bulletLeft = Bullet.left;
    int bulletRight = Bullet.right;

    if ((playerLeft < bulletRight) && (playerRight > bulletRight))
    {
        //  COLLISION !!
        //  [ ]       BULLET
        //   [ ]      PLAYER
        retIsCollide = true;
    }
    else if ((playerLeft < bulletLeft) && (playerRight > bulletLeft))
    {
        //  COLLISION !!
        //    [ ]     BULLET
        //   [ ]      PLAYER
        retIsCollide = true;
    }
    else if ((playerLeft > bulletLeft) && (playerRight < bulletRight))
    {
        //  COLLISION !!
        //  [   ]    BULLET
        //   [ ]     PLAYER
        retIsCollide = true;
    }
    else if ((playerLeft < bulletLeft) && (playerRight > bulletRight))
    {
        //  COLLISION !!
        //    |     BULLET
        //   [ ]    PLAYER
        retIsCollide = true;
    }
    else
    {
        //  NO COLLISION !!
    }

    return retIsCollide;
}
