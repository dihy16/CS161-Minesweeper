#include <iostream>
#include <fstream>
#include "main.h"
#include "functions.h"
#include "Console.h"
using std::chrono::system_clock;
Cell** cell;
Board board;
COORD CCursorPos;
bool BUsedKey = false;
short SPosX;
short SPosY;
bool isPlaying = false;

bool hasHighscore = false;

int timeToWrite = 0; // for file handling
int timeSaved = 0; // for output in saved game
bool isSavedGame = 0;
int highScore[3];

Timer timer;

std::ifstream fin;
std::ofstream fout;

// ***** TIMER FUNCTIONS *****
void timerStart() {
	timer.start = std::chrono::high_resolution_clock::now();
	timer.lastDisplay = 0;
	timer.BisRunning = true;
}

double timeDisplay() {
	if (timer.BisRunning) {
		timer.current = std::chrono::high_resolution_clock::now();
		return std::chrono::duration<double> (timer.current - timer.start).count();
	}
	return 0;
}

void drawTimer() {
	if (timer.BisRunning) {
		timer.timeDisplay = timeDisplay();
		if (isSavedGame) {
			timer.timeDisplay += timeSaved;
		}
		if (timer.timeDisplay - timer.lastDisplay >= 1 || timer.lastDisplay == 0) {
			gotoXY(0, 6);
			std::cout << "Time: " << timer.timeDisplay << " seconds" << std::flush;
			timer.lastDisplay = timer.timeDisplay;
		}
	}
}


void generate2DArray() {
	cell = new Cell * [board.SRow];
	for (int i = 0; i < board.SRow; i++) {
		cell[i] = new Cell[board.SCol];
	}
}

// ***** FILE HANDLING *****
// LOAD SAVED GAME
void readBoardDimension(std::ifstream& fin) {
	fin >> board.SRow >> board.SCol >> board.SBomb;
}

void readBoardAdjacentBombs(std::ifstream& fin) {
	short SRow = board.SRow;
	short SCol = board.SCol;
	short SBomb = board.SBomb;
	for (int i = 0; i < board.SRow; i++) {
		for (int j = 0; j < board.SCol; j++) {
			fin >> cell[i][j].SAdjacentBombs;
		}
	}
}

void readBoardFlagged(std::ifstream& fin) {
	short SRow = board.SRow;
	short SCol = board.SCol;
	short SBomb = board.SBomb;
	for (int i = 0; i < board.SRow; i++) {
		for (int j = 0; j < board.SCol; j++) {
			fin >> cell[i][j].BisFlagged;
			board.SFlagged += cell[i][j].BisFlagged;
		}
	}
}

void readBoardOpened(std::ifstream& fin) {
	short SRow = board.SRow;
	short SCol = board.SCol;
	short SBomb = board.SBomb;
	for (int i = 0; i < board.SRow; i++) {
		for (int j = 0; j < board.SCol; j++) {
			fin >> cell[i][j].BisOpened;
			board.SOpened += cell[i][j].BisOpened;
		}
	}
}

void readBoardBomb(std::ifstream& fin) {
	short SRow = board.SRow;
	short SCol = board.SCol;
	short SBomb = board.SBomb;
	for (int i = 0; i < SRow; i++) {
		for (int j = 0; j < SCol; j++) {
			fin >> cell[i][j].BBomb;
		}
	}
}

void writeBoardDimension(std::ofstream& fout) {
	fout << board.SRow << " " << board.SCol << " " << board.SBomb << std::endl;
}

void writeBoardAdjacentBombs(short SRow, short SCol, short SBomb, std::ofstream& fout) {
	for (int i = 0; i < SRow; i++) {
			for (int j = 0; j < SCol; j++) {
				fout << cell[i][j].SAdjacentBombs;
				if (j != SCol - 1)
					fout << " ";
			}
			fout << std::endl;
		}
}

void writeBoardFlagged(short SRow, short SCol, short SBomb, std::ofstream& fout) {
	for (int i = 0; i < SRow; i++) {
		for (int j = 0; j < SCol; j++) {
			if (cell[i][j].BisFlagged)
				fout << 1;
			else
				fout << 0;
			if (j != SCol - 1)
				fout << " ";
		}
		fout << std::endl;
	}
}

void writeBoardOpened(short SRow, short SCol, short SBomb, std::ofstream& fout) {
	for (int i = 0; i < SRow; i++) {
		for (int j = 0; j < SCol; j++) {
			if (cell[i][j].BisOpened)
				fout << 1;
			else
				fout << 0;
			if (j != SCol - 1)
				fout << " ";
		}
		fout << std::endl;
	}
}

void writeBoardBombs(short SRow, short SCol, short SBomb, std::ofstream& fout){
	for (int i = 0; i < SRow; i++) {
		for (int j = 0; j < SCol; j++) {
			if (cell[i][j].BBomb)
				fout << 1;
			else 
				fout << 0;
			if (j != SCol - 1)
				fout << " ";
		}
		fout << std::endl;
	}
}

// SAVE HIGHSCORE
const int NUM_SCORES = 3;

void readHighscore(int hi[], int size, std::ifstream& fin) {
	for (int i = 0; i < size; i++) {
		fin >> hi[i];
	}
}

void addHighscore(int time, int highScore[], int size) {
	for (int i = 0; i < size; i++) {
		if (highScore[i] == time) {
			break; // dont add duplicate scores
		}
		else if (highScore[i] > time) {
			if (i == 0)
				hasHighscore = true;
			for (int j = size - 1; j > i; j--) {
				highScore[j] = highScore[j - 1];
			}
			highScore[i] = time;
			break;
		}
	}
}

void writeHighscoreFile(std::ofstream& fout, int highScore[], int size) {
	for (int i = 0; i < size; i++) {
		fout << highScore[i] << std::endl;
	}
}
// save time in saved game
void writeTimeSaved(int time, std::ofstream& fout) {
	fout << time;
}

void readTimeSaved(std::ifstream& fin) {
	fin >> timeSaved;
}

void drawScoreboard(){
	std::string scoreboardText;
	scoreboardText = "SCOREBOARD";
	setColorBGTextXY(ConsoleWidth / 2 - scoreboardText.length() / 2 - 2, 4, 15, 2, scoreboardText);
	scoreboardText = "FIRST :";
	setColorBGTextXY(33, 6, 15, 0, scoreboardText);
	scoreboardText = "SECOND:";
	setColorBGTextXY(33, 7, 15, 0, scoreboardText);
	scoreboardText = "THIRD :";
	setColorBGTextXY(33, 8, 15, 0, scoreboardText);
	fin.open("highscore.txt");
	if (fin.is_open()) {
		readHighscore(highScore, NUM_SCORES, fin);
	}
	int y = 6;
	for (int i = 0; i < NUM_SCORES; i++) {
		gotoXY(41, y);
		std::cout << highScore[i];
		y++;
	}
}

// ****** 2D ARRAY ******
void generateBombs() {
	short SBomb = board.SBomb;
	short SJ, SI;
	srand(time(0));
	while (SBomb) {
		SJ = rand() % board.SCol;
		SI = rand() % board.SRow;
		if (cell[SI][SJ].BBomb) continue;
		else {
			cell[SI][SJ].BBomb = true;
			SBomb--;
		}
	}
}

void displayBombs() {
	for (int i = 0; i < board.SRow; i++) {
		for (int j = 0; j < board.SCol; j++) {
			if (cell[i][j].BBomb)
				std::cout << "X";
			else std::cout << 0;
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void dele2DArray() {
	for (int i = 0; i < board.SRow; i++) {
		delete[] cell[i];
	}
	delete[] cell;
}

void boardPos() {
	SPosX = (ConsoleWidth / 2) - board.SCol;
	SPosY = (ConsoleHeight / 2 - board.SRow) / 2 + 13;
}

void drawIngameMenu(short SMode, short SIndex) {
	SMenuPos = SIndex;
	SFunctions = 2;
	std::string menuModeText;
	if (SMode == 1) {
		menuModeText = "  SAVE GAME  ";
		setColorBGTextXY(ConsoleWidth / 2 - menuModeText.length() / 2 - 3, 3, 15, (SIndex == 0) ? 2 : 0, menuModeText);
	}
	if (SMode == 2) {
		menuModeText = "  NEW GAME  ";
		setColorBGTextXY(ConsoleWidth / 2 - menuModeText.length() / 2 - 3, 3, 15, (SIndex == 0) ? 2 : 0, menuModeText);
	}
	if (SMode == 3) {
		menuModeText = "  NEW GAME  ";
		setColorBGTextXY(ConsoleWidth / 2 - menuModeText.length() / 2 - 3, 3, 15, (SIndex == 0) ? 2 : 0, menuModeText);
	}
	if (SMode >= 1) {
		menuModeText = "  RETURN  ";
		setColorBGTextXY(ConsoleWidth / 2 - menuModeText.length() / 2 - 3, 4, 15, (SIndex == 1) ? 2 : 0, menuModeText);
	}
}

void create(short SRow, short SCol, short SBomb) {
	board.SRow = SRow;
	board.SCol = SCol;
	board.SBomb = SBomb;
	board.SOpened = 0;
	board.SFlagged = 0;

	generate2DArray();
	generateBombs();
	boardPos();
	CCursorPos = { 0, 0 };
	isPlaying = true;
	drawBoard();
	//for (int i = 0; i < board.SCol; i++) {
	//	for (int j = 0; j < board.SRow; j++) {
	//		if (cell[i][j].BBomb) {
	//			drawCell(j, i, 10);
	//		}
	//	}
	//}
	drawGameStatus(1);
	drawIngameMenu(0, 0);
	timerStart();
	//displayBombs();
	/*std::cout << std::endl;
	displayMine();*/
	//dele2DArray(); 
}

short posX(short SX) {
	return (SX * 2 + SPosX);
}

short posY(short SY) {
	return (SY + SPosY);
}

// ***** DRAWING TO CONSOLE *****

void drawCell(short SX, short SY, short SKieu) {
	switch (SKieu)
	{
	case 0: // empty cell
		setColorBGTextXY(posX(SX), posY(SY), 0, 10, "  ");
		break;
	case 1: // 1
		setColorBGTextXY(posX(SX), posY(SY), 9, 15, "1 ");
		break;
	case 2: // 2
		setColorBGTextXY(posX(SX), posY(SY), 10, 15, "2 ");
		break;
	case 3: // 3
		setColorBGTextXY(posX(SX), posY(SY), 12, 15, "3 ");
		break;
	case 4: // 4
		setColorBGTextXY(posX(SX), posY(SY), 1, 15, "4 ");
		break;
	case 5: // 5
		setColorBGTextXY(posX(SX), posY(SY), 4, 15, "5 ");
		break;
	case 6: // 6
		setColorBGTextXY(posX(SX), posY(SY), 3, 15, "6 ");
		break;
	case 7: // 7
		setColorBGTextXY(posX(SX), posY(SY), 0, 15, "7 ");
		break;
	case 8: // 8
		setColorBGTextXY(posX(SX), posY(SY), 13, 15, "8 ");
		break;
	case 9: // B - Bomb
		setColorBGTextXY(posX(SX), posY(SY), 0, 12, "B ");
		break;
	case 10: // P - Flagged
		setColorBGTextXY(posX(SX), posY(SY), 12, 14, "P ");
		break;
	case 11: // Px - Flagged no bomb
		setColorBGTextXY(posX(SX), posY(SY), 15, 6, "Px");
		break;
	case 12: // B - Flagged have bomb
		setColorBGTextXY(posX(SX), posY(SY), 12, 14, "B ");
		break;
	case 13: // Cursor
		setColorBGTextXY(posX(SX) + 1, posY(SY), 0, 13, " ");
		break;
	case 14: // Cell at even pos
		setColorBGTextXY(posX(SX), posY(SY), 0, 7, "  ");
		break;
	case 15: // Cell at odd pos
		setColorBGTextXY(posX(SX), posY(SY), 0, 8, "  ");
		break;
	}
}

void drawBoard() {
	for (int i = 0; i < board.SRow; i++) {
		for (int j = 0; j < board.SCol; j++) {
			if (cell[i][j].BisFlagged) {
				drawCell(j, i, 10);
			}
			else if (cell[i][j].SAdjacentBombs > 0) {
				drawCell(j, i, cell[i][j].SAdjacentBombs);
			}
			else if (cell[i][j].BisOpened) {
				drawCell(j, i, 0);
			}
			else if ((i + j) % 2 != 0) {
				drawCell(j, i, 14);
			}
			else {
				drawCell(j, i, 15);
			}
			if (BUsedKey) {
				drawCell(CCursorPos.X, CCursorPos.Y, 13);
			}
		}
	}
}

void drawLine() {
	for (int i = 0; i < ConsoleWidth - 2; i++) {
		std::cout << char(45);
	}
}

void drawGameStatus(short SStatus) {
	setColor(7);
	gotoXY(0, 3);
	std::cout << "MAP  : " << board.SRow << " x " << board.SCol << std::endl;
	std::cout << "MINES: " << board.SBomb - board.SFlagged << " ";
	gotoXY(ConsoleWidth - 22, 4);
	std::cout << "GAME STATUS: ";
	switch (SStatus) {
	case 1:
		std::cout << "PLAYING";
		break;
	case 2:
		std::cout << "WON!";
		break;
	case 3:
		std::cout << "LOST";
		break;
	}
	std::cout << std::endl;
	drawLine();
}

void drawTitle() {
	drawLine();
	setColorBGTextXY(30, 1, 15, 4, "   MINESWEEPER  ");
	std::cout << std::endl;
	setColor(7);
	drawLine();
}

void drawMenu(short SIndex) {
	SMenuPos = SIndex;
	SFunctions = 4;
	std::string mainMenuText = "    NEW GAME    ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 1, 7, 15, (SIndex == 0) ? 2 : 0, mainMenuText);
	mainMenuText = "   RESUME GAME  ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 1, 8, 15, (SIndex == 1) ? 2 : 0, mainMenuText);
	mainMenuText = "    HIGHSCORE   ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 1, 9, 15, (SIndex == 2) ? 2 : 0, mainMenuText);
	mainMenuText = "      QUIT      ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 1, 10, 15, (SIndex == 3) ? 2 : 0, mainMenuText);
}

void drawLevelMenu(short SIndex) {
	SMenuPos = SIndex;
	SFunctions = 5;
	std::string mainMenuText = "   DIFFICULTY  ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 3, 7, 15, 0, mainMenuText);
	mainMenuText = " Height      Width      Mines  ";
	setColorBGTextXY(ConsoleWidth / 2 - 8, 8, 15, 0, mainMenuText);
	mainMenuText = "EASY                  9          9         10    ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 2, 9, 15, (SIndex == 0) ? 2 : 0, mainMenuText);
	mainMenuText = "INTERMEDIATE         16         16         40    ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 2, 10, 15, (SIndex == 1) ? 2 : 0, mainMenuText);
	mainMenuText = "EXPERT               24         24         80    ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 2, 11, 15, (SIndex == 2) ? 2 : 0, mainMenuText);
	mainMenuText = "   CUSTOM GAME  ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 2, 12, 15, (SIndex == 3) ? 2 : 0, mainMenuText);
	mainMenuText = "    RETURN    ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 + 20, 13, 15, (SIndex == 4) ? 2 : 0, mainMenuText);
}

void drawInputBoard() {
	SFunctions = 1;
	std::string mainMenuText = "CUSTOM GAME";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 2, 5, 15, 0, mainMenuText);
	std::cout << std::endl;
	mainMenuText = "Input the HEIGHT of the board:  ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 4, 7, 15, 0, mainMenuText);
	mainMenuText = "Input the WIDTH of the board:  ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 5, 8, 15, 0, mainMenuText);
	mainMenuText = "Input the number of MINES:  ";
	setColorBGTextXY(ConsoleWidth / 2 - mainMenuText.length() / 2 - 6, 9, 15, 0, mainMenuText);
}




// ***** GAME EVENTS *****
bool BisValidCell(short SX, short SY) {
	return (SX >= 0 && SX < board.SRow && SY >= 0 && SY < board.SCol);
}

bool BcanOpen(short SX, short SY) {
	return (!cell[SX][SY].BisOpened && !cell[SX][SY].BisFlagged);
}

short SCountBombs(short SX, short SY) {
	short SNum = 0;
	short dx[]{ 1, -1, 0, 0, 1, -1, 1, -1 };
	short dy[]{ 0, 0, 1, -1, 1, -1, -1, 1 };
	for (int i = 0; i < 8; i++) {
		short newX = SX + dx[i];
		short newY = SY + dy[i];
		if (BisValidCell(newX, newY)) {
			if (cell[newX][newY].BBomb)
				SNum++;
		}
	}
	return SNum;
}

void winGame() {
	timer.BisRunning = false;
	if (isSavedGame)
		isSavedGame = false;
	timeToWrite = timer.lastDisplay;
	fin.open("highscore.txt");
	if (fin.is_open()) {
		readHighscore(highScore, NUM_SCORES, fin);
		fin.close();
	}
	addHighscore(timeToWrite, highScore, NUM_SCORES);

	fout.open("highscore.txt");
	if (fout.is_open()) {
		writeHighscoreFile(fout, highScore, NUM_SCORES);
		fout.close();
	}
	SPage = 5;
	for (int i = 0; i < board.SCol; i++) {
		for (int j = 0; j < board.SRow; j++) {
			if (cell[i][j].BBomb) {
				drawCell(j, i, 10);
			}
		}
	}
	isPlaying = false;
	dele2DArray();
	deleteRow(4, 1);
	setColor(7);
	gotoXY(0, 3);
	std::cout << "MAP  : " << board.SRow << " x " << board.SCol << std::endl;
	std::cout << "MINES: 0";
	gotoXY(ConsoleWidth / 2 - 7, 7);
	std::cout << "YOU WON!!";
	if (hasHighscore) {
		gotoXY(ConsoleWidth / 2 - 15, 8);
		std::cout << "YOU REACHED NEW HIGHSCORE!";
		hasHighscore = 0;
	}
	drawIngameMenu(2, 0);
}

void loseGame() {
	SPage = 4;
	timer.BisRunning = false;
	if (isSavedGame)
		isSavedGame = false;
	for (int i = 0; i < board.SCol; i++) {
		for (int j = 0; j < board.SRow; j++) {
			if (cell[i][j].BisFlagged) {
				if (cell[i][j].BBomb)
					drawCell(j, i, 12);
				else
					drawCell(j, i, 11);
			}
			else if (cell[i][j].BBomb)
				drawCell(j, i, 9);
		}
	}
	isPlaying = false;
	dele2DArray();
	deleteRow(4, 1);
	setColor(7);
	gotoXY(0, 3);
	std::cout << "MAP  : " << board.SRow << " x " << board.SCol << std::endl;
	std::cout << "MINES: " << board.SBomb - board.SFlagged << " ";
	gotoXY(ConsoleWidth / 2 - 7, 7);
	std::cout << "YOU LOST!!";
	
	drawIngameMenu(3, 0);
}

void openCell(short SX, short SY) {
	if (BcanOpen(SX, SY)) {
		cell[SX][SY].BisOpened = true;
		if (cell[SX][SY].BBomb) {
			loseGame();
		}
		else {
			board.SOpened++;
			short numBomb = SCountBombs(SX, SY);
			if (numBomb > 0) {
				cell[SX][SY].SAdjacentBombs = numBomb;
			}
			else {
				short dx[]{ 1, -1, 0, 0, 1, -1 };
				short dy[]{ 0, 0, 1, -1, 1, -1 };
				for (int i = 0; i < 6; i++) {
					short newX = SX + dx[i];
					short newY = SY + dy[i];
					if (BisValidCell(newX, newY)) {
						openCell(newX, newY);
					}
				}
			}
		}
	}
}

bool hasWon() {
	return (board.SBomb + board.SOpened == board.SCol * board.SRow);
}

void inputBoard(short& x, short& y, short& z) {
	gotoXY(ConsoleWidth - 29, 7);
	std::cin >> x;
	gotoXY(ConsoleWidth - 29, 8);
	std::cin >> y;
	gotoXY(ConsoleWidth - 29, 9);
	std::cin >> z;
}



// ***** KEY HANDLING *****
void leftClick(short SX, short SY) {
	if (BcanOpen(SX, SY)) {
		openCell(SX, SY);
	}
	if (isPlaying) {
		drawBoard();
		drawGameStatus(1);
		if (hasWon()) {
			winGame();
		}
	}
}

void rightClick(short SX, short SY) {
	if (!cell[SX][SY].BisOpened ) {
		if (!cell[SX][SY].BisFlagged) {
			cell[SX][SY].BisFlagged = true;
			board.SFlagged++;
		}
		else {
			cell[SX][SY].BisFlagged = false;
			board.SFlagged--;
		}
	}
	drawBoard();
	//deleteRow(4, 1);
	drawGameStatus(1);
	//drawLine();
}

/* 
SPage index:
1. Main menu
2. Difficulty
3. Game board
4. Lost
5. Win
6. Custom (from page 2)
7. Scoreboard
*/

void keyboardHandle(KEY_EVENT_RECORD key) {
	if (key.bKeyDown) {
		switch (key.wVirtualKeyCode)
		{
		case VK_UP:
			switch (SPage) {
			case 1:
				if (SMenuPos == 0)
					SMenuPos = SFunctions - 1;
				else
					SMenuPos--;
				drawMenu(SMenuPos);
				break;
			case 2:
				if (SMenuPos == 0)
					SMenuPos = SFunctions - 1;
				else
					SMenuPos--;
				drawLevelMenu(SMenuPos);
				break;
			case 3:
				if (isPlaying) {

					BUsedKey = true;
					if (CCursorPos.Y == 0)
						CCursorPos.Y = board.SRow - 1;
					else
						CCursorPos.Y -= 1;
					drawBoard();
					drawGameStatus(1);
				}
				else {
					drawIngameMenu(1, (SMenuPos == 1 ? 0 : 1));
				}
				break;
			case 4:
				drawIngameMenu(3, (SMenuPos == 1 ? 0 : 1));
				break;
			case 5:
				drawIngameMenu(2, (SMenuPos == 1 ? 0 : 1));
				break;
			}
		break;
		case VK_DOWN:
			switch (SPage) {
			case 1:
				if (SMenuPos == SFunctions - 1)
					SMenuPos = 0;
				else
					SMenuPos++;
				drawMenu(SMenuPos);
				break;
			case 2:
				if (SMenuPos == SFunctions - 1)
					SMenuPos = 0;
				else
					SMenuPos++;
				drawLevelMenu(SMenuPos);
				break;
			case 3:
				if (isPlaying) {
					BUsedKey = true;
					if (CCursorPos.Y == board.SRow - 1)
						CCursorPos.Y = 0;
					else
						CCursorPos.Y += 1;
					drawBoard();
					drawGameStatus(1);
				}
				else {
					drawIngameMenu(1, (SMenuPos == 0 ? 1 : 0));
				}
				break;
			case 4:
				drawIngameMenu(3, (SMenuPos == 0 ? 1 : 0));
				break;
			case 5:
				drawIngameMenu(2, (SMenuPos == 0 ? 1 : 0));
				break;
			}
			break;
		case VK_LEFT:
			if (isPlaying) {
				BUsedKey = true;
				if (CCursorPos.X == 0)
					CCursorPos.X = board.SCol - 1;
				else
					CCursorPos.X -= 1;
				drawBoard();
				drawGameStatus(1);
			}
			break;
		case VK_RIGHT:
			if (isPlaying) {
				BUsedKey = true;
				if (CCursorPos.X == board.SCol - 1)
					CCursorPos.X = 0;
				else
					CCursorPos.X += 1;
				drawBoard();
				drawGameStatus(1);
			}
			break;
		case VK_RETURN: // ENTER key
			switch (SPage)
			{
			case 1:
				switch (SMenuPos)
				{
				case 0:
					SPage = 2;
					deleteRow(4, 5);
					drawLevelMenu(0);
					break;
				case 1:
				{
					SPage = 3;
					deleteRow(7, 7);
					// load game from file
					fin.open("dimension.txt");
					if (fin.is_open()) {
						readBoardDimension(fin);
						fin.close();
					}
					board.SOpened = 0;
					board.SFlagged = 0;
					generate2DArray();

					fin.open("bomb.txt");
					if (fin.is_open()) {
						readBoardBomb(fin);
						fin.close();
					}
					fin.open("opened.txt");
					if (fin.is_open()) {
						readBoardOpened(fin);
						fin.close();
					}
					fin.open("flagged.txt");
					if (fin.is_open()) {
						readBoardFlagged(fin);
						fin.close();
					}
					fin.open("adjaBomb.txt");
					if (fin.is_open()) {
						readBoardAdjacentBombs(fin);
						fin.close();
					}
					boardPos();
					CCursorPos = { 0, 0 };
					isPlaying = true;
					drawBoard();
					drawGameStatus(1);
					drawIngameMenu(0, 0);
					timerStart();
					fin.open("boardTime.txt");
					if (fin.is_open()) {
						readTimeSaved(fin);
						fin.close();
					}
					isSavedGame = true;
				}
					break;
				case 2:
					SPage = 7;
					deleteRow(3, ConsoleHeight - 3);
					drawScoreboard();
					break;
				case 3:
					exit(0);
					break;
				}
				break;
			case 2:
				switch (SMenuPos)
				{
				case 0:
					SPage = 3;
					deleteRow(7, 7);
					create(9, 9, 10);
					//gotoXY(0, 6);
					//timer.update();
					break;
				case 1:
					SPage = 3;
					deleteRow(7, 7);
					create(16, 16, 40);
					break;
				case 2:
					SPage = 3;
					deleteRow(7, 7);
					create(24, 24, 80);
					break;
				case 3: // Create custom game
				{
					SPage = 6;
					deleteRow(7, 7);
					drawInputBoard();
					Cursor(true);
					short x = 0;
					short y = 0;
					short z = y;
					inputBoard(x, y, z);
					while (x * y == 0 || z > x * y || x < 0 || y < 0 || z < 0) {
						deleteRow(7, 3);
						drawInputBoard();
						setColorBGTextXY(ConsoleWidth / 2 - 10, 11, 15, 4, "  INVALID BOARD! ");
						inputBoard(x, y, z);
					}
					deleteRow(5, 7);
					SPage = 3;
					Cursor(false);
					create(x, y, z);
				}
					break;
				case 4:
					SPage = 1;
					deleteRow(7, 7);
					drawMenu(0);
					break;
				}
			break;
			case 3:
			{
				if (SMenuPos == 1) {
					SPage = 1;
					deleteRow(3, ConsoleHeight - 3);
					drawMenu(0);
				}
				else {
					fout.open("dimension.txt");
					if (fout.is_open()) {
						writeBoardDimension(fout);
						fout.close();
					}
					fout.open("bomb.txt");
					if (fout.is_open()) {
						writeBoardBombs(board.SRow, board.SCol, board.SBomb, fout);
						fout.close();
					}
					fout.open("opened.txt");
					if (fout.is_open()) {
						writeBoardOpened(board.SRow, board.SCol, board.SBomb, fout);
						fout.close();
					}
					fout.open("flagged.txt");
					if (fout.is_open()) {
						writeBoardFlagged(board.SRow, board.SCol, board.SBomb, fout);
						fout.close();
					}
					fout.open("adjaBomb.txt");
					if (fout.is_open()) {
						writeBoardAdjacentBombs(board.SRow, board.SCol, board.SBomb, fout);
						fout.close();
					}
					fout.open("boardTime.txt");
					if (fout.is_open()) {
						writeTimeSaved(timer.timeDisplay, fout);
						fout.close();
					}
					setColorBGTextXY(ConsoleWidth / 2 - 14, 6,10, 0, "YOUR GAME HAS BEEN SAVED");
				}
			}
			break;
			case 4:
			{
				if (SMenuPos == 1) { // if choose "Return"
					SPage = 1;
					deleteRow(3, ConsoleHeight - 3);
					drawMenu(0);
				}
				else if (SMenuPos == 0) { // new game
					SPage = 3;
					deleteRow(3, 30);
					create(board.SRow, board.SCol, board.SBomb);
				}
			}
			break;
			case 5:
			{
				if (SMenuPos == 1) { // if choose "Return"
					SPage = 1;
					deleteRow(3, ConsoleHeight - 3);
					drawMenu(0);
				}
				else if (SMenuPos == 0) { // new game
					SPage = 3;
					deleteRow(3, ConsoleHeight - 3);
					create(board.SRow, board.SCol, board.SBomb);
				}
			}
			break;
			case 6:
				if (SMenuPos == 1) { // if choose "Return"
					SPage = 1;
					deleteRow(3, ConsoleHeight - 3);
					drawMenu(0);
				}
				else if (SMenuPos == 0) {

				}
			}
			break;
		case VK_ESCAPE: // ESC key
			switch (SPage)
			{
			case 1:
				exit(0);
				break;
			case 2:
				SPage = 1;
				deleteRow(8, 10);
				drawMenu(0);
				break;
			case 3:
				if (isPlaying) {
					if (isSavedGame) {
						isSavedGame = false;
					}
					timer.BisRunning = false;
					isPlaying = false;
					drawIngameMenu(1, 0);
				}
				else {
					SPage = 1;
					deleteRow(3, ConsoleHeight - 3);
					// dele2DArray();
					drawMenu(0);
				}
				break;
			case 5:
				SPage = 1;
				deleteRow(3, ConsoleHeight - 3);
				drawMenu(0);
				break;
			case 4:
				SPage = 2;
				deleteRow(3, ConsoleHeight - 3);
				drawLevelMenu(0);
				break;
			case 6:
				SPage = 2;
				deleteRow(3, ConsoleHeight - 3);
				drawLevelMenu(0);
				break;
			case 7:
				SPage = 1;
				deleteRow(3, ConsoleHeight - 3);
				drawMenu(0);
				break;
			}
			break;
		case LeftClick:
			if (isPlaying)
				leftClick(CCursorPos.Y, CCursorPos.X);
			break;
		case RightClick:
			if (isPlaying)
				rightClick(CCursorPos.Y, CCursorPos.X);
			break;
		}
	}
}

void eventHandle() {
	while (true) {
		if (timer.BisRunning) {
			drawTimer();
		}
		DWORD NumberOfEvents = 0;
		DWORD NumberOfEventsRead = 0;

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		GetNumberOfConsoleInputEvents(HConsoleInput, &NumberOfEvents);

		if (NumberOfEvents) {
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[NumberOfEvents];
			ReadConsoleInput(HConsoleInput, IREventBuffer, NumberOfEvents, &NumberOfEventsRead);
			for (DWORD i = 0; i < NumberOfEvents; i++) {
				if (IREventBuffer[i].EventType == KEY_EVENT) {
					keyboardHandle(IREventBuffer[i].Event.KeyEvent);
				}
			}
			delete[] IREventBuffer;
		}
	}
}


