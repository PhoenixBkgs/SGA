#pragma once
#include "GameUnit.h"
#include "EnumState.h"
#include "ImageKomastar.h"

class Item : public GameUnit
{
private:
    E_ITEM_TYPE         m_itemType;
    ImageKomastar*      m_itemImg;
    BYTE                m_imgAlpha;
public:
    Item();
    ~Item();

    void Start();
    void Update();
    void Render();

    void SetItemImg(ImageKomastar* Image) { m_itemImg = Image; }
    
    E_ITEM_TYPE GetItemType() { return m_itemType; }
    void        SetItemType(E_ITEM_TYPE ItemType) { m_itemType = ItemType; }

    BYTE GetImgAlpha() { return m_imgAlpha; }
    void SetImgAlpha(BYTE Alpha) { m_imgAlpha = Alpha; }
};

