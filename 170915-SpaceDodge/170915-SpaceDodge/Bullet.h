#pragma once
class Bullet
{
//=======================================================
//  VARIABLES
private:
    RECT m_bulletRect;
    vector<double> m_moveSpeed;

public:
    Bullet();
    ~Bullet();


//=======================================================
//  FUNCTIONS
private:
    void Setup();

public:
    void Update();
    void Render(HDC hdc);

    RECT* GetBulletRect() { return &m_bulletRect; }
};

