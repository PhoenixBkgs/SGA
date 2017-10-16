#pragma once
class GameObject;
class ImageObject;
class SpritesObject
{
private:
    GameObject*  m_gameObj;
    ImageObject* m_spritesImg;

    int     m_currFrameX;
    int     m_currFrameY;
    int     m_maxFrameX;
    int     m_maxFrameY;
    int     m_triggerPosX;

public:
    SpritesObject();
    ~SpritesObject();

#pragma region GET
    int     GetFrameX() { return m_currFrameX; }
    int     GetFrameY() { return m_currFrameY; }
    int     GetMaxFrameX() { return m_maxFrameX; }
    int     GetMaxFrameY() { return m_maxFrameY; }
    bool    IsTriggerFrame();
#pragma endregion

#pragma region SET
    void SetGameObject(GameObject* GameObj) { m_gameObj; }
    void SetSpritesImg(ImageObject* Image) { m_spritesImg = Image; }
    void SetFrameX(int FrameX) { m_currFrameX = FrameX; }
    void SetFrameY(int FrameY) { m_currFrameY = FrameY; }
    void SetMaxFrameX(int MaxFrameX) { m_maxFrameX = MaxFrameX; }
    void SetMaxFrameY(int MaxFrameY) { m_maxFrameY = MaxFrameY; }
    void SetTriggerPos(int Pos) { m_triggerPosX = Pos; }
    void NextFrame();
#pragma endregion

    void ValidateFramePos();

#pragma region RENDER
    void Render(HDC hdc);
#pragma endregion

};

