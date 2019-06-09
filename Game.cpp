#include "include.h"

const int SizeY = 22;  // SizeField [Pixels] / SizeTile
const int SizeX = 12;  // SizeField [Pixels] / SizeTile
const int SizeTile = 45;
const int WField = 27; //[Pixels]

struct aKeyBoardControl
    {
    int left, up, right, down;
    };

struct Point
    {int x, y;};

Point posOfFigur[4] = {};  // TODO del from global list

void keyBoardControl (int Field[SizeY][SizeX], const aKeyBoardControl theControl);
bool checkBorder (int Field[SizeY][SizeX]);
void RotateFigure (int Field[SizeY][SizeX]);
void StepPlayGame (int Field[SizeY][SizeX], bool cheatMode, int* ColorNum, int* NumBrick);
void DrawPlayGame (int Field[SizeY][SizeX], HDC tiles, HDC background, int ColorNum);
void CheakIsLineReady (int Field[SizeY][SizeX], int* NLines);
int PlayGame(HDC tiles, HDC background, bool cheatMode);
void CreatNewFigure (bool cheatMode, int* NumBrick, int* ColorNum);
void copyArray (Point oldArr [], Point newArr [], int lenArr);

void PrintScore (int NLines);
void PrintTime (int timer);
//void PrintNextFigure (int Field[SizeY][SizeX], HDC tiles);

const int Figures[7][4] =
    {
    {1, 3, 5, 7}, // I  0
    {2, 4, 5, 7}, // Z  1
    {3, 5, 4, 6}, // S  2
    {3, 5, 4, 7}, // T  3
    {2, 3, 5, 7}, // L  4
    {3, 5, 7, 6}, // J  5
    {2, 3, 4, 5}  // O  6
    };

int PlayGame (HDC tiles, HDC background, bool cheatMode)
    {


    Music music;//создаем объект музыки
    music.openFromFile("music.ogg");//загружаем файл
    music.play();//воспроизводим музыку
    int Field[SizeY][SizeX] = {0};

    int NumBrick = rand() % 6;

    int ColorNum = 1 + rand() % 7;

    int NLines = 0;

    int timer = GetTickCount ();
    txBegin ();

    aKeyBoardControl Player = {'A', 'W', 'D', 'S'};


    CreatNewFigure (cheatMode, &NumBrick, &ColorNum);

    while (checkBorder(Field))
        {
        StepPlayGame(Field, cheatMode, &ColorNum, &NumBrick);

        keyBoardControl (Field, Player);

        CheakIsLineReady (Field, &NLines);

        DrawPlayGame (Field, tiles, background, ColorNum);

        PrintScore (NLines);

        PrintTime (timer);

        //PrintNextFigure (Field, tiles);

        txSleep (100);
        }

    for (int y = 0; y < SizeY; y++)
        for (int x = 0; x < SizeX; x++)
            Field [y][x] = 0;

    NLines = 0;

    PrintTime(timer);

    return 0;
    }

//====================================================
/*void PrintNextFigure (int Field[SizeY][SizeX], HDC tiles)
    {
    for (int i = 0; i < SizeY; i++)
        {

        txBitBlt (txDC (), 625, 90, SizeTile, SizeTile, tiles, Field [y][x] * SizeTile, 0);
        }
    } */

//====================================================

void PrintTime (int timer)
    {
    timer = GetTickCount () - timer;

    char textOfTime [50] = "";
    unsigned n = sprintf (textOfTime, "%i:%i", timer/60000, timer/1000);
    assert (n < sizeof (textOfTime) - 1);

    txSetColor (TX_BLACK);

    if (txFontExist ("Impact")) txSelectFont ("Impact", 100);
    if (txFontExist ("Ubuntu")) txSelectFont ("Ubuntu", 150);

    txDrawText (621, 824, 799, 979, textOfTime);
    }

//====================================================

void PrintScore (int NLines)
    {
    char lines [10] = "";
    sprintf (lines, "%i", NLines*10);
    txSetColor (TX_BLACK);

    if (txFontExist ("Impact")) txSelectFont ("Impact", 100);
    if (txFontExist ("Ubuntu")) txSelectFont ("Ubuntu", 150);

    txDrawText (621, 585, 799, 736, lines);
    }

//====================================================

void CreatNewFigure (bool cheatMode, int* NumBrick, int* ColorNum)
    {
    if (cheatMode) *NumBrick = 0;

    else *NumBrick = rand() % 6;

    *ColorNum = 1 + rand() % 7;

    for (int i = 0; i < 4; i++)
        {
        posOfFigur[i].x = Figures[*NumBrick][i] % 2 + SizeX / 2;

        posOfFigur[i].y = Figures[*NumBrick][i] / 2;
        }
    }

//====================================================

void CheakIsLineReady (int Field[SizeY][SizeX], int* NLines)
    {
    int nLines = SizeY-1;

	for (int y = SizeY-1; y > 0; y--)
        {
		int count = 0;

		for (int x = 0; x < SizeX; x++)
            {
		    if (Field [y][x]) count++;
		    Field [nLines][x] = Field [y][x];
            }


		if (count < SizeX) nLines-- ;
		else (*NLines) ++;
        }
     }

//====================================================

void DrawPlayGame (int Field[SizeY][SizeX], HDC tiles, HDC background, int ColorNum)   // DrawField
    {

    txBitBlt (txDC (), 0, 0, WndSize.x, WndSize.y, background);

    for (int y = 0; y < SizeY; y++)
        for (int x = 0; x < SizeX; x++)
            {

            if (Field[y][x] == 0) continue;

            txBitBlt (txDC (), x*SizeTile + WField, y*SizeTile, SizeTile, SizeTile, tiles, Field [y][x] * SizeTile, 0);
            }

    for (int i = 0; i < 4; i++)
        {

        txBitBlt (txDC (), posOfFigur [i].x * SizeTile + WField, posOfFigur [i].y * SizeTile, SizeTile, SizeTile, tiles, ColorNum * SizeTile, 0);
        }
    }

//====================================================

void StepPlayGame (int Field[SizeY][SizeX], bool cheatMode, int* ColorNum, int* NumBrick)   // UpdatePlayGame
    {
    Point oldPosOfFigur [4] = {0};

    copyArray (oldPosOfFigur, posOfFigur, 4);

    for (int i = 0; i < 4; i++)
        {
        posOfFigur [i].y += 1;
        }

    if (!checkBorder (Field))
        {
        for (int i = 0; i < 4; i++) {Field [oldPosOfFigur[i].y][oldPosOfFigur[i].x] = *ColorNum;}

        CreatNewFigure (cheatMode, NumBrick, ColorNum);
        }
    }

//====================================================

void keyBoardControl (int Field[SizeY][SizeX], const aKeyBoardControl theControl)
    {
    Point oldPosOfFigur [4] = {0};

    copyArray (oldPosOfFigur, posOfFigur, 4);

    int dx = 0;

    if (GetAsyncKeyState (theControl.right))
        dx = +1;

    if (GetAsyncKeyState (theControl.left))
        dx = -1;

    if (GetAsyncKeyState (theControl.up))
        {
        RotateFigure (Field);
        txSleep (10);
        }

    for (int i = 0; i < 4; i++) { oldPosOfFigur [i] = posOfFigur [i]; posOfFigur [i].x += dx; }

    if (!checkBorder (Field))
        for (int i = 0; i < 4; i++) posOfFigur [i] = oldPosOfFigur [i];
    }

//====================================================

bool checkBorder (int Field[SizeY][SizeX])
    {
    for (int i = 0; i < 4; i++)
        {
        if (posOfFigur [i].x < 0 || posOfFigur [i].x >= SizeX || posOfFigur [i].y >= SizeY) return false;

        else if (Field [posOfFigur [i].y] [posOfFigur [i].x]) return false;
        }

    return true;
    }

//====================================================

void RotateFigure (int Field[SizeY][SizeX])
    {
    Point oldPosOfFigur [4] = {0};

    copyArray (oldPosOfFigur, posOfFigur, 4);

    Point p = posOfFigur [1];

    for (int i = 0; i < 4; i++)
        {
        int x  = posOfFigur [i].y - p.y;
        int y  = posOfFigur [i].x - p.x;

        posOfFigur [i].x =    p.x -   x;
        posOfFigur [i].y =    p.y +   y;
        }

    if (!checkBorder (Field)) for (int i = 0; i < 4; i++) posOfFigur [i] = oldPosOfFigur [i];
    }

//====================================================

void copyArray (Point oldArr [], Point newArr [], int lenArr)
    {
    for (int i = 0; i < lenArr; i++) {oldArr [i] = newArr [i];}
    }
