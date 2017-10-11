#pragma once
#include "ImageKomastar.h"

class GameNode
{
private:
    ImageKomastar* m_backBuffer;
public:
    GameNode();
    virtual ~GameNode();

    virtual void Start() PURE;
    virtual void Update();
    virtual void Render() PURE;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    ImageKomastar* GetBackbuffer() { return m_backBuffer; }
};

