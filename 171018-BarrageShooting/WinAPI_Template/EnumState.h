#pragma once
enum E_GAME_STATE
{
    GAME_LOADING = 0, GAME_READY, GAME_LOBBY, GAME_PLAYING, GAME_PAUSE, GAME_CLEAR, GAME_OVER, GAME_END
};

enum E_PLAYER_STATE
{
    PLAYER_IDLE = 0, PLAYER_RUN, PLAYER_JUMP, PLAYER_DJUMP, PLAYER_END
};

enum E_WEAPON_TYPE
{
    WEAPON_SINGLESHOT = 0, WEAPON_MAGNUM, WEAPON_BUCKSHOT, WEAPON_BARRAGE, WEAPON_END
};

enum E_IMAGE_LOAD_KIND
{
    LOAD_EMPTY, LOAD_FILE, LOAD_END
};

enum E_ITEM_TYPE
{
    ITEM_SCORE = 0, ITEM_HEAL, ITEM_END
};