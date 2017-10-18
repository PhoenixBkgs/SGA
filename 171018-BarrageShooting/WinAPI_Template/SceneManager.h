#pragma once
#include "SingletonBase.h"
#include "GameObject.h"

class SceneManager : public SingletonBase<SceneManager>
{
private:
    map<string, GameObject*>                m_mapScene;
    map<string, GameObject*>::iterator      m_mapIter;
    
    map<string, vector<GameObject*>>        m_mapSceneTest;
    vector<GameObject*>                     m_vecGameObj;
    vector<GameObject*>::iterator           m_vecIter;
public:
    void AddGameObject(GameObject* GameObj);
    void AddGameObject(string Key, GameObject* GameObj);

    void Update(string Key);
    void Render(string Key);
};

