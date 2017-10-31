#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{
    cout << "GameNode()" << endl;
    g_pKeyManager->Setup();
    g_pLogManager->Setup("\\Log\\");

    m_pImgBackBuffer = g_pImgManager->AddImage("back-buffer", W_WIDTH, W_HEIGHT);
}


GameNode::~GameNode()
{
    g_pKeyManager->ReleaseInstance();
    g_pLogManager->ReleaseInstance();
    g_pImgManager->ReleaseInstance();
    g_pDrawHelper->ReleaseInstance();
    g_pGeoHelper->ReleaseInstance();

    delete m_pImgBackBuffer;
}

void GameNode::Update()
{
    InvalidateRect(g_hWnd, NULL, false);
}

LRESULT GameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    g_hDC = this->m_pImgBackBuffer->GetMemDC();

    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, REFRESH_RATE, NULL);
        break;
    case WM_TIMER:
        this->Update();
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        this->Render();
        this->m_pImgBackBuffer->FastRender(hdc);
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
