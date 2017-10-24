#pragma once
#include "GameObject.h"

class ProjectileObject : public GameObject
{
private:
    UnitPos             m_genPos;
    UnitPos             m_destPos;
    vector<UnitPos>     m_snapshotPos;
    bool                m_bUseMoveSpeed;

public:
    ProjectileObject();
    ~ProjectileObject();

    virtual void Update() override;
    virtual void Render() override;

#pragma region GET

#pragma endregion
#pragma region SET

#pragma endregion


    void Setup(UnitPos GenPos, UnitPos DestPos);
    void MoveToPos();
    void MoveToPosBezier();
};

