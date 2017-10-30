#pragma once
#include "GameObject.h"
#include "TileObject.h"

#define TILE_COL_COUNT 20
#define TILE_ROW_COUNT 6

class MapObject : public GameObject
{
private:
    vector<TileObject>      m_vecTiles;
    ImageObject*            m_imgTile;
	HBRUSH					m_brush;

    ImageObject*            m_pWorldmap;
    UnitSize                m_nMapSize;
	ImageObject*			m_pFogImg;
	ImageObject*			m_pMinimap;
	ImageObject*			m_pMapbuffer;

public:
    MapObject();
    ~MapObject();

#pragma region GET
	vector<TileObject>*		GetMapTiles() { return &m_vecTiles; }
#pragma endregion
#pragma region SET
    void    SetMapSize(UnitSize MapSize) { m_nMapSize = MapSize; }
#pragma endregion


    void Start();
    virtual void Update() override;
    virtual void Render() override;
};

