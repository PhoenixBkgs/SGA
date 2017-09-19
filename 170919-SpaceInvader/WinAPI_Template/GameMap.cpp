#include "stdafx.h"
#include "GameMap.h"


GameMap::GameMap()
{
    Setup();
}


GameMap::~GameMap()
{
}

void GameMap::Setup()
{
    LeftWall = { -MAP_DEFAULT_SIZE, 0, 0, W_HEIGHT };
    RightWall = { W_WIDTH, 0, W_WIDTH + MAP_DEFAULT_SIZE, W_HEIGHT };
    TopWall = { 0, -MAP_DEFAULT_SIZE, W_WIDTH, 0 };
    BottomWall = { 0, W_HEIGHT, W_WIDTH, W_HEIGHT + MAP_DEFAULT_SIZE };

    POINT ptEnemyDest;
    ptEnemyDest.x = 0;
    ptEnemyDest.y = (int)(W_HEIGHT * 0.7);

    EnemyDestWall = { ptEnemyDest.x, ptEnemyDest.y, W_WIDTH, ptEnemyDest.y + MAP_DEFAULT_SIZE };
}

bool GameMap::IsCollision(RECT * Rect1, RECT * Rect2)
{
    RECT rt;
    return IntersectRect(&rt, Rect1, Rect2);
}

bool GameMap::IsEnemyArrive(RECT * EnemyRect)
{
    return IsCollision(&EnemyDestWall, EnemyRect);
}

bool GameMap::IsRectOutside(RECT * Rect, int LeftRight)
{
    if (LeftRight == 0)
    {
        //  LEFT
        return IsCollision(&LeftWall, Rect);
    }
    else
    {
        return IsCollision(&RightWall, Rect);
    }
}

bool GameMap::IsBulletArrive(RECT * BulletRect)
{
    return IsCollision(&TopWall, BulletRect);
}
