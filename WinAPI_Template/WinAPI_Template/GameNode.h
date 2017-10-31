#pragma once
#include "ImageObject.h"

class GameNode
{
protected:
    ImageObject* m_pImgBackBuffer;

public:
    GameNode();
    virtual ~GameNode();

    virtual void Start() PURE;
    virtual void Update();
    virtual void Render() PURE;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};