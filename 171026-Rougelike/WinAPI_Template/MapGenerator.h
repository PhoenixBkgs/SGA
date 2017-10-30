#pragma once
#include "SpritesObject.h"

enum TILE_TYPE
{
    TILE_EMPTY = 0, WALL, SPIKE_LEFT, SPIKE_TOP, SPIKE_RIGHT, SPIKE_BOTTOM, GEM_AMETHYST, GEM_GOLD, GEM_JADE, GEM_EMERALD, GEM_SILVER, TILE_END
};

class MapGenerator
{
private:
    vector<SpritesObject>  m_vecObjects;
    HBRUSH          m_brushTransparent;
    ImageObject*    m_imgBackground;
    ImageObject*    m_imgWorldMap;
	string	        m_szMapData;
    string          m_szFilename;
	int		        m_nMapCol;
	int		        m_nMapRow;
    int             m_nTileSize;
    double          m_dMagnifier;

    UnitSize        m_nMapSize;

	SpritesObject*	m_sprTile;			//	20 x 20px _ 5 x 1
    SpritesObject*	m_sprObstacle;		//	20 x 20px _ 4 x 1
    SpritesObject*	m_sprGem;			//	20 x 20px _ 5 x 1

public:
	MapGenerator();
	~MapGenerator();

#pragma region GET
	int		GetMapCol() { return m_nMapCol; }
	int		GetMapRow() { return m_nMapRow; }
    UnitSize GetMapSize() { return m_nMapSize; }
    vector<SpritesObject>  GetGameObjects() { return m_vecObjects; }
#pragma endregion
#pragma region SET
	void	SetMapCol(int Col) { m_nMapCol = Col; }
	void	SetMapRow(int Row) { m_nMapRow = Row; }
#pragma endregion

    void LoadImageResources();
    void Setup(string MapFilename);

    void SaveMap(HDC hdc, string Filename);
};