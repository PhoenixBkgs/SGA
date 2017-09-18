// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

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
#define WINNAME (LPCWSTR)(TEXT("TITLE"))
#define WINSTARTX		0
#define WINSTARTY		0
#define WINSIZEX		640
#define WINSIZEY		720
#define WINSTYLE		WS_CAPTION | WS_SYSMENU
#define PURE			= 0

//==================================================================
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//==================================================================


//==================================================================
//		## 매니져 추가 ##
//==================================================================
#include "KeyManager.h"

#define g_pKeyManager KeyManager::GetInstance()

//==================================================================
//		## 전역변수 ##
//==================================================================
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;
extern HBITMAP      g_hbmBall;