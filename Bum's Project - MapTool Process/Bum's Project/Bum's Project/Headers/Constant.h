#pragma once

extern HWND g_hWnd;

const int WINCX = 800;
const int WINCY = 600;

const WORD MIN_STR	  = 64;
const WORD MIDDLE_STR = 128;
const WORD MAX_STR	  = 256;

const int TILECX = 94;
const int TILECY = 48;

//
const float SLOW_SPEED_PLAYER = 1.5f;
const float MOTION_SPEED_PLAYER = 1.3f;
const float ATTACK_SPEED_PLAYER = 2.f;
const float ATTACK_SPEED_WEAPON = ATTACK_SPEED_PLAYER;
const float SKILL_SPEED_PLAYER = 1.1f;
const float TARGET_SPEED = 2.3f;
const float MOTION_DAMAGE_MONSTER = 3.f;

const float DEAD_UP_SPEED   = 0.5f;
const int   DEAD_ALPA_SPEED = 1;

const DWORD ITEM_WEAPON = 0x00000001;
const DWORD ITEM_ARMOR	= 0x00000002;
const DWORD ITEM_POTION = 0x00000004;


const int TTT = -100;
const int YYY = -80;