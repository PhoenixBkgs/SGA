#pragma once
#include "SpritesObject.h"

class Item : public SpritesObject
{
private:
    E_ITEM_TYPE         m_itemType;
    int                 m_nScore;

public:
    Item();
    ~Item();

#pragma region GET
    E_ITEM_TYPE     GetItemType() { return m_itemType; }
    int     GetScore() { return m_nScore; }
#pragma endregion

#pragma region SET
    void    SetItemType(E_ITEM_TYPE Type) { m_itemType = Type; }
    void    SetScore(int Score) { m_nScore = Score; }
#pragma endregion

    virtual void Update() override;
    virtual void Render() override;

    Item GenItem(UnitPos GenPos, UnitSize Size);
};

