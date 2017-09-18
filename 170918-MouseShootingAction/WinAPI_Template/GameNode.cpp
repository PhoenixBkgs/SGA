#include "stdafx.h"
#include "GameNode.h"



HDC          hdcMem;
HBITMAP      hbmMem;
HANDLE       hOld;
PAINTSTRUCT  ps;
HDC          hdc;

GameNode::GameNode()
{
    g_pKeyManager->Setup();
}


GameNode::~GameNode()
{
    g_pKeyManager->ReleaseInstance();
}

void GameNode::Update()
{
    InvalidateRect(g_hWnd, NULL, false);
}

LRESULT GameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 15, NULL);
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
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        hdcMem = CreateCompatibleDC(hdc);
        hbmMem = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);

        hOld = SelectObject(hdcMem, hbmMem);
        BitBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, hdcMem, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hOld);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);

        this->Render(hdc);
        EndPaint(hWnd, &ps);
        break;
    }
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
