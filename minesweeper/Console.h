#pragma once
#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>
#include <conio.h>
#include <string>

void resizeConsole(SHORT width, SHORT height);
void clrscr(void);
void gotoXY(SHORT x, SHORT y);
SHORT wherex();
SHORT wherey();
void setColor(WORD color);
void setBackgroundColor(WORD color);
void setColorBGTextXY(int x, int y, int t_color, int b_color, std::string name);
void Cursor(BOOL bVisible = TRUE, DWORD dwSize = 25);
void deleteRow(SHORT SStartPos, SHORT SNumberRow);