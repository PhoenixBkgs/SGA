#pragma once
class MenuScene
{
private:
    vector<GameObject*>*     m_vecGameObj;

public:
    MenuScene();
    ~MenuScene();

    void Setup();

    vector<GameObject*>* GetGameObjs() { return m_vecGameObj; }
};


