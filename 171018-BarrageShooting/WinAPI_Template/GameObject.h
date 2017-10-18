#pragma once

//  Mutual Refernce
class ImageObject;

class GameObject
{
    //  VARS
private:
    int             m_uId;              //  Unique
    string          m_szTagName;        //  TagName

//--------------------------------------------------------------------------
//      BODY
    RECT            m_rtBody;           //  Body rectangle
    ImageObject*    m_imgBody;          //  Image paste on body rect
    UnitPos         m_dPos;             //  Center position of Object
    UnitSpeed       m_dSpeed;           //  Move to XY each Move() function
    UnitSize        m_nSize;            //  Width, Height of body rect
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
//      HIT BOX
    RECT            m_rtHitBox;         //  Hit box for calc only
    UnitSize        m_nSizeHBox;        //  Hit box size
    RectMargin      m_nMarginHBox;      //  Hit box margin
//--------------------------------------------------------------------------

    bool            m_isVisible;        //  Render or not
    bool            m_isMovable;        //  Move or not
    bool            m_isRigid;          //  Collide or not
    bool            m_isAlive;
    double          m_dAlpha;
    double          m_dAngle;

    int             m_nLife;

    //  FUNCS
public:
    GameObject();
    ~GameObject();
#pragma region GET
    //  Identifier
    int         GetUid() { return m_uId; }
    string      GetTagName() { return m_szTagName; }
    //  Body
    RECT        GetBodyRect() { return m_rtBody; }
    UnitPos     GetPos() { return m_dPos; }
    UnitSize    GetSize() { return m_nSize; }
    UnitSpeed   GetSpeed() { return m_dSpeed; }
    //  HitBox
    RECT        GetHBoxRect() { return m_rtHitBox; }
    UnitSize    GetHBoxSize() { return m_nSizeHBox; }

    bool        IsVisible() { return m_isVisible; }
    bool        IsAlive() { return m_isAlive; }
    int         GetLife() { return m_nLife; }
#pragma endregion

#pragma region SET
    //  Identifier
    void SetUid(int Id) { m_uId = Id; }
    void SetTagName(string TagName) { m_szTagName = TagName; }
    //  Body
    void SetBodyRect(RECT Rect);
    void SetBodySize(UnitSize Size) { m_nSize = Size; }
    void SetBodySpeed(UnitSpeed Speed) { m_dSpeed = Speed; }
    void SetBodyPos(UnitPos Pos) { m_dPos = Pos; }
    //  Body image
    void SetBodyImg(ImageObject* Image) { m_imgBody = Image; }
    void SetBodyImgAuto();
    void SetBodyImgByKey(string Key, bool IsOverwrite = false);
    //  HitBox
    void SetHBoxMargin(RectMargin HBoxMargin) { m_nMarginHBox = HBoxMargin; }

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
