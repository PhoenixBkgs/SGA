#pragma once
class GameNode
{
public:
    GameNode();
    virtual ~GameNode();

    virtual void Update();
    virtual void Render(HDC hdc) PURE;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

