#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "Physics2DKomastar.h"
#include "ImageKomastar.h"
#include "PuzzleUnit.h"

#define COL_COUNT 6
#define ROW_COUNT 3
#define MAX_PUZZLE_PCS 18
#define WIN_MARGIN 100
#define PUZZLE_SIZE 200
#define SHUFFLE_LIMITER 100

class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    Draw2DKomastar      m_drawHelper;
    Geometry2DKomastar  m_geoHelper;
    Physics2DKomastar   m_physicsHelper;

    ImageKomastar*      m_img;
    vector<PuzzleUnit>  m_vecPuzzle;

    bool                m_isPlaying;
    int                 m_shuffleIdx;
    int                 m_prevShuffleIdx;
    int                 m_shuffleCount;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    void PlayerController();
    void SystemController();

    void PuzzleShuffle();
    void PuzzleExchange(PuzzleUnit* Puzzle1, PuzzleUnit* Puzzle2);
};