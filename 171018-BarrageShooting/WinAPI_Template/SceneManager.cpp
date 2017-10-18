#include "stdafx.h"
#include "SceneManager.h"

void SceneManager::AddGameObject(GameObject * GameObj)
{
    string Key = GameObj->GetTagName();
    AddGameObject(Key, GameObj);
}

void SceneManager::AddGameObject(string Key, GameObject * GameObj)
{
    //m_mapScene.insert(pair<string, GameObject*>(Key, GameObj));
    auto findObj = m_mapScene.find(Key);
    if (findObj != m_mapScene.end())
    {
        findObj->second.push_back(GameObj);
    }
    else
    {
        m_mapScene.insert(pair<string, vector<GameObject*>>(Key, m_vecGameObj));
        findObj = m_mapScene.find(Key);
        findObj->second.push_back(GameObj);
    }
}

void SceneManager::Update(string Key)
{
    /*
    m_mapIter = m_mapScene.find(Key);
    while (m_mapIter != m_mapScene.end())
    {
        m_mapIter->second->Update();
        m_mapIter++;
    }
    */
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
    /*
    m_mapIter = m_mapScene.find(Key);
    while (m_mapIter != m_mapScene.end())
    {
        m_mapIter->second->Render();
        m_mapIter++;
    }
    */
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
