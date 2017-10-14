#pragma once
#include "GameUnit.h"
#include "ImageKomastar.h"

#define HOLE_PCS_WIDTH 50

class Hole : public GameUnit
{
private:
    ImageKomastar* m_img;
public:
    Hole();
    ~Hole();

    void Start();
    void Update();
    void Render();

    void SetImg(ImageKomastar* Img) { m_img = Img; }
};

