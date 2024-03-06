#include <iostream>
#include "main.h"
#include "functions.h"
#include "Console.h"
short SPage, SMenuPos, SFunctions;
int main() {
	resizeConsole(ConsoleWidth, ConsoleHeight);
	SetConsoleTitle(TEXT("Minesweeper_Dinh_Ho_Gia_Huy"));
	drawTitle();
	Cursor(false);

	SPage = 1;
	drawMenu(1);
	eventHandle();
	return 0;
}

