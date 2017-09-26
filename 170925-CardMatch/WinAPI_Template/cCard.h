#pragma once
#define MAX_CARD 10
#define IMG_WIDTH 120
#define IMG_HEIGHT 200

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

