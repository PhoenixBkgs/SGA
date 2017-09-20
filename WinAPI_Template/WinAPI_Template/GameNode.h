#pragma once
class GameNode
{
public:
    GameNode();
    virtual ~GameNode();

    virtual void Start() PURE;
    virtual void Update();
    virtual void Render() PURE;

    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

