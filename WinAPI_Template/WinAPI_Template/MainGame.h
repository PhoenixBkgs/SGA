#pragma once
#include "GameNode.h"
#include "Player.h"
#include "ImageObject.h"
#include "GeometryHelper.h"

#define BG_WIDTH 6600
#define BG_HEIGHT 675

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    GeometryHelper m_geoHelper;
    ImageObject* m_img;
    ImageObject* m_img2;
    
    UnitPos pos;
    UnitPos pt1;
    UnitPos pt2;
    UnitPos pt3;
    double  dAngle;
    int count;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
};