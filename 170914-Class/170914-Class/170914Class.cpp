// 170914Class.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"

int main()
{
    srand(time(NULL));
    rand();

    MainGame* game = new MainGame;
    bool isPlaying = true;

    while (isPlaying)
    {
        isPlaying = game->MainPlay();
    }

    return 0;
}

