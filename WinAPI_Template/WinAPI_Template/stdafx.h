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
#include <map>
#include <time.h>
#include <chrono>
#include <iostream>
#include <assert.h>

using namespace std;

//==================================================================
//		## 디파인문 - 메크로 ## (윈도우창 초기화)
//==================================================================
#define W_NAME (LPCWSTR)(TEXT("TITLE"))
#define W_START_POS_X		0
#define W_START_POS_Y		0
#define W_WIDTH		        1600
#define W_HEIGHT		    900
#define WINDOW_STYLE		WS_CAPTION | WS_SYSMENU
#define PURE			    = 0

#define REFRESH_RATE        10
#define MAGENTA_COLOR       RGB(255, 0, 255)

//==================================================================
//		## MACRO FUNCTION ##
//==================================================================
#define SAFE_DELETE(p)          { if(p) { delete(p); (p) = NULL; } }
#define SAFE_DELETE_ARRAY(p)    { if(p) { delete[]{p); (p) = NULL; } } }


//==================================================================
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//==================================================================
#include "DataStructure.h"

//==================================================================
//		## 매니져 추가 ##
//==================================================================
#include "KeyManager.h"
#include "LogManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "TimerManager.h"

#define g_pKeyManager KeyManager::GetInstance()
#define g_pLogManager LogManager::GetInstance()
#define g_pImgManager ImageManager::GetInstance()
#define g_pScnManager SceneManager::GetInstance()
#define g_pTimerManager TimerManager::GetInstance()

//==================================================================
//		## Helper 추가 ##
//==================================================================
#include "DrawHelper.h"
#include "GeometryHelper.h"
#include "PhysicsHelper.h"

#define g_pDrawHelper DrawHelper::GetInstance()
#define g_pGeoHelper GeometryHelper::GetInstance()
#define g_pPhxsHelper PhysicsHelper::GetInstance()

#define GLOBAL_WIN_SIZE     UnitSize{W_WIDTH, W_HEIGHT}
#define GLOBAL_WIN_HSIZE    UnitSize{W_WIDTH * 0.5f, W_HEIGHT * 0.5f}
#define GLOBAL_CENTER_POS   UnitPos{W_WIDTH * 0.5f, W_HEIGHT * 0.5f}

//==================================================================
//		## 전역변수 ##
//==================================================================
extern HINSTANCE	g_hInst;
extern HWND			g_hWnd;
extern POINT		g_ptMouse;
extern HDC          g_hDC;