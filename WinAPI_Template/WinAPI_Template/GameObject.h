#pragma once

//  Mutual Refernce
class ImageObject;

class GameObject
{
//  VARS
private:
    int             m_uId;
    string          m_szTagName;
    RECT            m_rtBody;
    ImageObject*    m_imgBody;
    RECT            m_rtHitBox;
    
    UnitPos         m_dPos;
    UnitSpeed       m_dSpeed;
    UnitSize        m_nSize;

    bool            m_isVisible;
    bool            m_isAlive;
    double          m_dAlpha;
    double          m_dAngle;

//  FUNCS
public:
    GameObject();
    ~GameObject();
#pragma region GET
    //  GET
    int         GetUid() { return m_uId; }
    string      GetTagName() { return m_szTagName; }
    RECT        GetBodyRect() { return m_rtBody; }
    RECT        GetHitBoxRect() { return m_rtHitBox; }
    UnitPos     GetPos() { return m_dPos; }
    UnitSize    GetSize() { return m_nSize; }
    UnitSpeed   GetSpeed() { return m_dSpeed; }
    bool        IsVisible() { return m_isVisible; }
    bool        IsAlive() { return m_isAlive; }
#pragma endregion

#pragma region SET
    //  SET
    void SetUid(int Id) { m_uId = Id; }
    void SetTagName(string TagName) { m_szTagName = TagName; }
    void SetImgBody(ImageObject* Image) { m_imgBody = Image; }
    void SetSize(UnitSize Size) { m_nSize = Size; }
    void SetSpeed(UnitSpeed Speed) { m_dSpeed = Speed; }
    void SetPos(UnitPos Pos) { m_dPos; }
    void SetVisible() { m_isVisible = true; }
    void SetInvisible() { m_isVisible = false; }
    void SetAlive() { m_isAlive = true; }
    void SetDead() { m_isAlive = false; }
#pragma endregion

    //  Update / Render
    virtual void Update();
    virtual void Render();

    //  Object move
    virtual void Move();

};

