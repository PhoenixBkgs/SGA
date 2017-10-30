#pragma once
#include "SpritesObject.h"
#define ENEMY_MOVE_SPEED 2.0f

class Enemy : public SpritesObject
{
private:
    ImageObject*    m_destDC;
    UnitPos*        m_dMapPos;
public:
    Enemy();
    ~Enemy();

    void SetMapPos(UnitPos* MapPos) { m_dMapPos = MapPos; }

    virtual void Update() override;
    virtual void Render() override;
};

