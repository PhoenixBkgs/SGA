#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <time.h>

using namespace std;

//==================================================================
//		## 디파인문 - 메크로 ## (윈도우창 초기화)
//==================================================================
#define WIN_NAME (LPCWSTR)(TEXT("SPACE DODGE"))
#define WIN_POS_X		0
#define WIN_POS_Y		0
#define WIN_WIDTH		640
#define WIN_HEIGHT		720
#define WIN_STYLE		WS_CAPTION | WS_SYSMENU
#define PURE			= 0

//==================================================================
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//==================================================================


//==================================================================
//		## 전역변수 ##
//==================================================================
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;