#pragma once
#include "GameNode.h"
#include "Player.h"
#include "Draw2DKomastar.h"
#include "Geometry2DKomastar.h"
#include "Physics2DKomastar.h"
#include "ImageKomastar.h"
#include "PuzzleUnit.h"

//  IMAGE SIZE 1200 x 600
#define COL_COUNT 6
#define ROW_COUNT 3
#define MAX_PUZZLE_PCS 18
#define PUZZLE_SIZE 200
#define SHUFFLE_LIMITER 10

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

    bool                m_isClear;
    bool                m_isPlaying;
    bool                m_isShowImage;
    bool                m_isShuffling;

    int                 m_matchCount;
    int                 m_moveCount;

    int                 m_shuffleIdx;
    int                 m_prevShuffleIdx;
    int                 m_shuffleCount;
    int                 m_marginLeft;
    int                 m_marginTop;

    double              m_txtPosY;
    double              m_clearScreenOpacity;
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

    void PuzzleMove(int Direction);
    void PuzzleExchange(PuzzleUnit* Puzzle1, PuzzleUnit* Puzzle2);

    void MatchChecker();
};