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
    virtual void Render(HDC hdc) = 0;       //  순수 가상함수

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

