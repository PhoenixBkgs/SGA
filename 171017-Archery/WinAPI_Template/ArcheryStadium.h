#pragma once
#include "GameMapObject.h"
#define BOARD_HEIGHT 300

class Wind;
class ArcheryStadium : public GameMapObject
{
private:
    Wind*           m_pWind;

public:
    ArcheryStadium();
    ~ArcheryStadium();

#pragma region SET
    void SetWind(Wind* Wind) { m_pWind = Wind; }
#pragma endregion

    void Setup();
    void Render();
};

