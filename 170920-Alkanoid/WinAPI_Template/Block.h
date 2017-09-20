#pragma once
#include "GameNode.h"
#include "GameUnit.h"
#include "DrawHelper.h"

#define BLOCK_WIDTH     100
#define BLOCK_HEIGHT    20

class Block : public GameNode, public GameUnit
{
private:
    int m_R;
public:
    Block();
    ~Block();

    // GameNode��(��) ���� ��ӵ�
    virtual void Start() override;
    virtual void Render() override;
    void Update();
};

