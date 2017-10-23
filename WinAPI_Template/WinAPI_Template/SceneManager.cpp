#include "stdafx.h"
#include "SceneManager.h"

void SceneManager::AddGameObjToScn(GameObject * GameObj)
{
    string Key = GameObj->GetTagName();
    AddGameObjToScn(Key, GameObj);
}

void SceneManager::AddGameObjToScn(string Key, GameObject * GameObj)
{
    auto findObj = m_mapScene.find(Key);
    if (findObj != m_mapScene.end())
    {
        findObj->second.push_back(GameObj);
    }
    else
    {
        vector<GameObject*> vecGameObj;
        m_mapScene.insert(pair<string, vector<GameObject*>>(Key, vecGameObj));
        findObj = m_mapScene.find(Key);
        findObj->second.push_back(GameObj);
    }
}

vector<GameObject*>* SceneManager::FindSceneByKey(string Key)
{
    return &m_mapScene.find(Key)->second;
}

void SceneManager::DeleteSceneByKey(string Key)
{
    vector<GameObject*>* vecGameObj = FindSceneByKey(Key);
    if (vecGameObj->size() > 0)
    {
        vecGameObj->clear();
        m_mapScene.erase(Key);
    }
}

void SceneManager::DeleteAllScene()
{
    m_mapIter = m_mapScene.begin();
    while (m_mapIter != m_mapScene.end())
    {
        m_mapIter->second.clear();
        m_mapIter = m_mapScene.erase(m_mapIter);
    }
}

void SceneManager::Update(string Key)
{
    if (m_mapScene.find(Key) == m_mapScene.end())
    {
        return;
    }
    vector<GameObject*> vecGameObj = m_mapScene.find(Key)->second;
    int size = (int)vecGameObj.size();
    for (int i = 0; i < size; i++)
    {
        vecGameObj[i]->Update();
    }
}

void SceneManager::Render(string Key)
{
    if (m_mapScene.find(Key) == m_mapScene.end())
    {
        return;
    }
    vector<GameObject*> vecGameObj = m_mapScene.find(Key)->second;
    int size = (int)vecGameObj.size();
    for (int i = 0; i < size; i++)
    {
        vecGameObj[i]->Render();
    }
}
