#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{
    g_pKeyManager->Setup();
    g_pLog4K->Setup("\\Log\\");
}


GameNode::~GameNode()
{
    g_pKeyManager->ReleaseInstance();
    g_pLog4K->ReleaseInstance();
}

void GameNode::Update()
{
    InvalidateRect(g_hWnd, NULL, true);
}

LRESULT GameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 10, NULL);
        break;
    case WM_TIMER:
        this->Update();
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_PAINT:
        g_hDC = BeginPaint(hWnd, &ps);
        this->Render();
        EndPaint(hWnd, &ps);
        break;
    case WM_MOUSEMOVE:
        g_ptMouse.x = LOWORD(lParam);
        g_ptMouse.y = HIWORD(lParam);
        break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
