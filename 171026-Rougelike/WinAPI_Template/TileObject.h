#pragma once
#include "GameObject.h"

class TileObject : public GameObject
{
private:
	int		m_nGridPosX;
	int		m_nGridPosY;

public:
    TileObject();
    ~TileObject();

    virtual void Update() override;
    virtual void Render(HDC hdc);

	void	SetGridPosX(int X) { m_nGridPosX = X; }
	void	SetGridPosY(int Y) { m_nGridPosY = Y; }
};