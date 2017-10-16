#pragma once
#define MAX_DELAY_COUNT 100.0f

class ImageObject;
class SpritesObject
{
private:
    //  IMAGE
    ImageObject*  m_pImg;

    //  FRAME
    int         m_currFrameX;
    int         m_currFrameY;
    int         m_maxFrameX;
    int         m_maxFrameY;
    double      m_delayCount;
    double      m_delayStep;

public:
    SpritesObject();
    ~SpritesObject();

    void Render();
    void NextFrame();

    //  GET SET
    POINT GetCurrFrame() { return POINT{ m_currFrameX, m_currFrameY }; }
    POINT GetMaxFrame() { return POINT{ m_maxFrameX, m_maxFrameY }; }

    void SetCurrFrame(POINT FramePoint) { m_currFrameX = FramePoint.x; m_currFrameY = FramePoint.y; }
    void SetDelayStep(double DelayStep) { m_delayStep = DelayStep; }
};

