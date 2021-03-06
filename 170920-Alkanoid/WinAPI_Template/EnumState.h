#pragma once

enum E_GAME_STATE
{
    GAME_READY = 0, GAME_PLAYING, GAME_PAUSE, GAME_CLEAR, GAME_OVER, GAME_END
};

enum E_EDGE
{
    LEFT_EDGE = 0, TOP_EDGE, RIGHT_EDGE, BOTTOM_EDGE, END_EDGE
};

enum E_DIRECTION
{
    DIR_L_U = 0, DIR_N_U, DIR_R_U, DIR_N_R, DIR_R_D, DIR_N_D, DIR_L_D, DIR_N_L, DIR_N_N
    //  0   1   2
    //  7   8   3
    //  6   5   4
};

enum E_REFLECT_DIR
{
    REVERSE_ALL = 0, REVERSE_X, REVERSE_Y, REVERSE_END
};

enum E_WEAPON_TYPE
{
    WEAPON_BULLET = 0, WEAPON_BUCKSHOT, WEAPON_TSAR, WEAPON_END
};

enum E_SHAPE
{
    SHAPE_RECT = 0, SHAPE_ELLIPSE, SHAPE_END
};

class EnumState
{
};


