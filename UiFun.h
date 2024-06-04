#ifndef __UIFUN_H__
#define __UIFUN_H__
#include "GameMode.h"
#pragma comment (lib, "winmm.lib")
#include <Windows.h>
#include <mmsystem.h>


#define _C 1046.502
#define _D 1108.731
#define _E 1318.510
#define _F 1396.913
#define _G 1567.982
#define _A 1760.000
#define _B 1975.533



void printHeadUI();
void printTailUI(int attempts, int remain, int find);
void printMultiUI(int attempts1, int attempts2, int remain1, int remain2, int find1, int find2);
#endif