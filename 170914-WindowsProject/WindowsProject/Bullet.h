#pragma once

using namespace std;

#define YPOS_OFFEST 200
#define GRAVITY 2
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 10

class Bullet
{
private:
    vector<RECT> m_vecBullet;
    int m_remainBullet;

public:
    Bullet();
    ~Bullet();

    int GetRemainBullet();

    void CreateBulletRain(int BulletCount);
    void DropBulletRain(Player* player);
    void DrawBulletRain(HDC hdc);
    bool CollisionValidate(RECT Player, RECT Bullet);
};

