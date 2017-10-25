#pragma once
#include "GameNode.h"
#include "json.hpp"

#pragma region SCENE
#include "GameScene.h"
#pragma endregion

typedef struct tagimage
{
    DWORD   resID;
    HDC     hMemDC;
    HBITMAP hBit;
    HBITMAP hOldBit;
    int     nWidth;
    int     nHeight;
    BYTE    btLoadType;

    tagimage()
    {
        resID = 0;
        hMemDC = NULL;
        hBit = NULL;
        hOldBit = NULL;
        nWidth = 0;
        nHeight = 0;
        btLoadType = 0;

    }
}  IMAGE_INFO, *LPIMAGE_INFO;

using json = nlohmann::json;
class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    E_GAME_STATE    m_gameState;
    GameScene*      m_scnGame;

    LPIMAGE_INFO	m_pBlendImage;
    BLENDFUNCTION   m_stBlendFunc;
//=======================================================
//  FUNCTIONS
private:
public:
    MainGame();
    ~MainGame();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;
    void Reset();

#pragma region RESOURCES
    void LoadAllResources();
    void LoadImageResources();
    void LoadSoundResources();
#pragma endregion
#pragma region CONTROLLER
    void    SystemController();
    void    MouseLock();
    void    MouseUnlock();
#pragma endregion
};