#pragma once
#include "GameObject.h"
#include "TileObject.h"

#define TILE_COL_COUNT 20
#define TILE_ROW_COUNT 6

class MapObject : public GameObject
{
private:
    string                  m_gameMapData;
    vector<TileObject>      m_vecTiles;
    ImageObject*            m_imgTile;
	HBRUSH					m_brush;

	ImageObject*			m_pSkyImg;
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

#pragma endregion


    void Start();
    virtual void Update() override;
    virtual void Render() override;

	void SaveBmp(HDC hdc);
};

