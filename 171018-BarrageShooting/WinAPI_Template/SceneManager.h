#pragma once
#include "SingletonBase.h"
#include "GameObject.h"

class SceneManager : public SingletonBase<SceneManager>
{
private:
    map<string, vector<GameObject*>>            m_mapScene;
    map<string, vector<GameObject*>>::iterator  m_mapIter;
    vector<GameObject*>::iterator               m_vecIter;

public:
#pragma region CRUD
    //  CREATE
    void AddGameObjToScn(GameObject* GameObj);
    void AddGameObjToScn(string Key, GameObject* GameObj);
    //  READ
    vector<GameObject*>* FindSceneByKey(string Key);
    //  UPDATE
    void Update(string Key);
    void Render(string Key);
    //  DELETE
    void DeleteSceneByKey(string Key);
    void DeleteAllScene();
#pragma endregion
};

