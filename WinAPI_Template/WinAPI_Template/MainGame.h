#pragma once
#include "GameNode.h"
#include "SpritesObject.h"
#include "json.hpp"

using json = nlohmann::json;
class MainGame : public GameNode
{
//=======================================================
//  VARIABLES
private:
    json j;
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