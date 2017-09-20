#pragma once
#include "stdafx.h"

class GameNode
{
private:
    POINT m_mousePos;

public:
    GameNode();
    virtual ~GameNode();

    virtual void Update();
    virtual void Render(HDC hdc) = 0;       //  ���� �����Լ�

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

