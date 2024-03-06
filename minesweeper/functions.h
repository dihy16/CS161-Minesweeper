#pragma once
void generate2DArray();
void dele2DArray();
void create(short SRow, short SCol, short SBomb);
void drawCell(short SX, short SY, short SKieu);
void drawBoard();
void generateBombs();
void displayBombs();
void eventHandle();
void drawTitle();
void drawGameStatus(short SStatus);
void winGame();
void loseGame();
void drawMenu(short SIndex);
void drawLevelMenu(short SIndex);
void drawTimer();
void drawInputBoard();
