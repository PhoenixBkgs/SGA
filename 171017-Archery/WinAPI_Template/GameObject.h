#pragma once

//  Mutual Refernce
class ImageObject;

class GameObject
{
//  VARS
protected:
    int             m_uId;          //  Unique
    string          m_szTagName;    //  TagName
    RECT            m_rtBody;       //  Body rectangle
    ImageObject*    m_imgBody;      //  Image paste on body rect
    RECT            m_rtHitBox;     //  Hit box
    
    UnitPos         m_dPos;         //  Center position of Object
    UnitSpeed       m_dSpeed;       //  Move to XY each Move() function
    UnitSize        m_nSize;        //  Width, Height of body rect

    bool            m_isVisible;
    bool            m_isAlive;
    double          m_dAlpha;
    double          m_dAngle;

    int             m_nLife;

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
    int         GetLife() { return m_nLife; }
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
    void SetLife(int Life) { m_nLife = Life; }
    void SumLife(int Deal) { m_nLife += Deal; }
#pragma endregion

    //  Update / Render
    virtual void Update();
    virtual void Render();

    //  Object move
    virtual void Move();
};

