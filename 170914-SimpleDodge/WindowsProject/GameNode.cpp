#include "stdafx.h"
#include "GameNode.h"

using namespace std;

GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

void GameNode::Update()
{
    //InvalidateRect(hWnd, NULL, true);
}
    
LRESULT GameNode::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:     //  창이 생성될때
        SetTimer(hWnd, 1, 10, NULL);
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_MOUSEMOVE:
        //  Get position of mouse
        GetCursorPos(&m_mousePos);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
