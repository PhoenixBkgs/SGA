#pragma once
#define MAX_CARD 140
#define HALF_CARD 70
#define IMG_WIDTH 60
#define IMG_HEIGHT 100

class cCard
{
    //  VARS
private:
public:
    int     m_uId;          //  UNIQUE ID
    int     m_cId;          //  Category ID
    RECT    m_rtBody;
    bool    m_isOpen;
    bool    m_isFinished;

public:
    cCard();
    ~cCard();
};

