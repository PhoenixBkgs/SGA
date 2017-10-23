#pragma once
#include "GameObject.h"

#define DELAY_RESET_VAL 0.0f

class ImageObject;
class SpritesObject : public GameObject
{
protected:
    ImageObject*    m_spritesImg;
    int             m_currFrameX;           //  Current sprites X position
    int             m_currFrameY;           //  Current sprites Y position
    int             m_maxFrameX;            //  Current sprites max of X
    int             m_maxFrameY;            //  Current sprites max of Y
    int             m_triggerPosX;          //  Event trigger frame's x position
    double          m_delayCounter;         //  Change value each frame
    double          m_frameDelay;           //  Delay key value each frame
    double          m_frameDelayStep;       //  Step of delay count

public:
    SpritesObject();
    ~SpritesObject();

#pragma region GET
    ImageObject* GetSpritesImg() { return m_spritesImg; }
    int     GetFrameX() { return m_currFrameX; }
    int     GetFrameY() { return m_currFrameY; }
    int     GetMaxFrameX() { return m_maxFrameX; }
    int     GetMaxFrameY() { return m_maxFrameY; }
    double  GetFrameDelay() { return m_frameDelay; }
    double  GetFrameDelayStep() { return m_frameDelayStep; }
    bool    IsTriggerFrame();
#pragma endregion

#pragma region SET
    void SetSpritesImg(ImageObject* Image) { m_spritesImg = Image; }
    void SetFrameX(int FrameX) { m_currFrameX = FrameX; }
    void SetFrameY(int FrameY) { m_currFrameY = FrameY; }
    void SetMaxFrameX(int MaxFrameX) { m_maxFrameX = MaxFrameX; }
    void SetMaxFrameY(int MaxFrameY) { m_maxFrameY = MaxFrameY; }
    void SetTriggerPos(int Pos) { m_triggerPosX = Pos; }
    void SetFrameDelay(double Delay) { m_frameDelay = Delay; }
    void SetFrameDelayStep(double DelayStep) { m_frameDelayStep = DelayStep; }
    void NextFrameX();           //  Automatic move next frame
    void NextFrameY();
#pragma endregion

    void SetupForSprites(int MaxFrameX, int MaxFrameY);
    void SetupDelay();          //  Ready for use delay
    void ValidateFramePos();    //  Frame position ceiling

#pragma region OVERRIDE
    virtual void Update() override;
    virtual void Render() override;
#pragma endregion

};

