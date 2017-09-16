#pragma once

struct InfoBarModel
{
    char GameLevel[50];
    char RemainBullet[20];
};



class UserInterface
{
    //  VARS
private:
public:
    InfoBarModel m_stInfoBar;

    //  FUNCS
private:

public:
    UserInterface();
    ~UserInterface();

    void Update();

    void SetInfoBar(int GameLevel, int RemainBullet);
    void DrawInfoBar(HDC* hdc);
};

