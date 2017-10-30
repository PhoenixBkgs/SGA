#pragma once
#include "SpritesObject.h"

#define VEHICLE_SPEED 2.0f

class Vehicle : public SpritesObject
{
private:
    ImageObject*    m_destDC;
public:
    Vehicle();
    ~Vehicle();

    void Setup();
    virtual void Update() override;
    virtual void Render() override;
};