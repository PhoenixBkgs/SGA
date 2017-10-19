#pragma once
#include "SingletonBase.h"
#include "GameObject.h"

class SceneManager : public SingletonBase<SceneManager>
{
private:
    map<string, vector<GameObject*>>        m_mapScene;
    vector<GameObject*>::iterator           m_vecIter;

public:
    void AddGameObject(GameObject* GameObj);
    void AddGameObject(string Key, GameObject* GameObj);

    void DeleteSceneByKey(string Key);
    void DeleteAllScene();

    void Update(string Key);
    void Render(string Key);
};

