#pragma once
#include "EnumState.h"

#define MAP_DEFAULT_SIZE 200

class GameMap
{
public:
    RECT LeftWall;
    RECT RightWall;
    RECT TopWall;
    RECT BottomWall;

    RECT EnemyDestWall;

public:
    GameMap();
    ~GameMap();

    void Setup();
    bool IsCollision(RECT* Rect1, RECT* Rect2);
    E_EDGE IsInsideWindow(RECT* Rect);
    bool IsEnemyArrive(RECT* EnemyRect);
    bool IsRectOutside(RECT* PlayerRect, int LeftRight);
    bool IsBulletArrive(RECT* BulletRect);
};

