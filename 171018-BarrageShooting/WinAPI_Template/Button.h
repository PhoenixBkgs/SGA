#pragma once
#include "SpritesObject.h"

class StartButton : public SpritesObject
{
public:
    bool                    m_bIsSetup;
    E_GAME_STATE*           m_currGameState;
    UnitSize                m_originSize;
    StartButton();
    ~StartButton();

    void Setup(UnitPos Pos, UnitSize Size);
    void SetState(E_GAME_STATE* State) { m_currGameState = State; }

    virtual void Update() override;
    virtual void Render() override;

};

class SelectButton : public SpritesObject
{

public:
    SelectButton();
    ~SelectButton();

    virtual void Update() override;
    virtual void Render() override;
};