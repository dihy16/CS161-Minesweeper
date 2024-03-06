#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>

#define ConsoleWidth 80
#define ConsoleHeight 35

#define LeftClick 0x41
#define RightClick 0x44

struct Board {
	short SRow = 0;
	short SCol = 0;
	short SBomb = 0;
	short SOpened = 0;
	short SFlagged = 0;
};

struct Cell {
	bool BBomb = false;
	bool BisFlagged = false;
	bool BisOpened = false;
	short SAdjacentBombs = 0;
};
struct Timer {
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point current;
	int timeDisplay;
	int lastDisplay;
	bool BisRunning = false;
};

extern short SPage, SMenuPos, SFunctions;