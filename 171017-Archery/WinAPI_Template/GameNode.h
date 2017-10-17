#pragma once
#include "ImageObject.h"

class GameNode
{
private:
    ImageObject* m_backBuffer;
public:
    GameNode();
    virtual ~GameNode();

    virtual void Start() PURE;
    virtual void Update();
    virtual void Render() PURE;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    ImageObject* GetBackbuffer() { return m_backBuffer; }
};