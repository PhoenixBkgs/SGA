#pragma once

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
    bool IsEnemyArrive(RECT* EnemyRect);
    bool IsPlayerOutside(RECT* PlayerRect, int LeftRight);
    bool IsBulletArrive(RECT* BulletRect);
};

