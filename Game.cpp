#include "TXLib104.h"

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

Point posOfFigur[4] = {}, oldPosOfFigur[4] = {};

void keyBoardControl (const aKeyBoardControl theControl);
bool checkBorder ();
void RotateFigure ();
void StepPlayGame (bool cheatMode, int* ColorNum, int* NumBrick);
void DrawPlayGame (HDC tiles, HDC background, int ColorNum);
void CheakIsLineReady (int* NLines);
int PlayGame(HDC tiles, HDC background, bool cheatMode);
void CreatNewFigure (bool cheatMode, int* NumBrick, int* ColorNum);
void PrintScore (int NLines);
void PrintTime (int timer);

int Field[SizeY][SizeX] = {0};

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
    int NumBrick = rand() % 6;
    int ColorNum = 1 + rand() % 7;

    int NLines = 0;

    //int speed = 0.5;

    int timer = GetTickCount ();
    //printf ("%i\NumBrick", checkBorder());
    txBegin ();

    aKeyBoardControl Player = {'A', 'W', 'D', 'S'};

    CreatNewFigure (cheatMode, &NumBrick, &ColorNum);

    while (checkBorder())
        {

        keyBoardControl (Player);

        StepPlayGame(cheatMode, &ColorNum, &NumBrick);

        CheakIsLineReady (&NLines);

        DrawPlayGame (tiles, background, ColorNum);

        PrintScore (NLines);

        PrintTime (timer);

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

void PrintTime (int timer)
    {
    timer = GetTickCount () - timer;

    char textOfTime [10] = "";
    sprintf (textOfTime, "%i:%i", timer/60000, timer/1000);
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

    //printf ("%i", NumBrick);

    *ColorNum = 1 + rand() % 7;

    for (int i = 0; i < 4; i++)
        {
        posOfFigur[i].x = Figures[*NumBrick][i] % 2 + SizeX / 2;

        posOfFigur[i].y = Figures[*NumBrick][i] / 2;
        }
    }

//====================================================

void CheakIsLineReady (int* NLines)
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

void DrawPlayGame (HDC tiles, HDC background, int ColorNum)   // DrawField
    {
    txBitBlt (txDC (), 0, 0, WndSize.x, WndSize.y, background);

    for (int i = 0; i < SizeY; i++)   // TODO change i to y; j to x
        for (int j = 0; j < SizeX; j++)
            {
            //printf ("%i", Field[i][j]);

            if (Field[i][j] == 0) continue;

            txBitBlt (txDC (), j*SizeTile + WField, i*SizeTile, SizeTile, SizeTile, tiles, Field [i][j] * SizeTile, 0);
            }

    for (int i = 0; i < 4; i++)
        {
        //printf ("x %i, y %i\NumBrick", posOfFigur [i].x, posOfFigur [i].y);

        txBitBlt (txDC (), posOfFigur [i].x * SizeTile + WField, posOfFigur [i].y * SizeTile, SizeTile, SizeTile, tiles, ColorNum * SizeTile, 0);
        }
    }

//====================================================

void StepPlayGame (bool cheatMode, int* ColorNum, int* NumBrick)   // UpdatePlayGame
    {
    for (int i = 0; i < 4; i++)
        {
        oldPosOfFigur [i] = posOfFigur [i];

        posOfFigur [i].y += 1;
        }

    if (!checkBorder ())
        {
        for (int i = 0; i < 4; i++) {Field [oldPosOfFigur[i].y][oldPosOfFigur[i].x] = *ColorNum;}

        CreatNewFigure (cheatMode, NumBrick, ColorNum);
        }
    }

//====================================================

void keyBoardControl (const aKeyBoardControl theControl)
    {
    int dx = 0;

    if (GetAsyncKeyState (theControl.right))
        dx = +1;

    if (GetAsyncKeyState (theControl.left))
        dx = -1;

    if (GetAsyncKeyState (theControl.up))
        RotateFigure ();
        txSleep (10);

    for (int i = 0; i < 4; i++) { oldPosOfFigur [i] = posOfFigur [i]; posOfFigur [i].x += dx; }

    if (!checkBorder ())
        for (int i = 0; i < 4; i++) posOfFigur [i] = oldPosOfFigur [i];
    }

//====================================================

bool checkBorder ()
    {
    for (int i = 0; i < 4; i++)
        {
        if (posOfFigur [i].x < 0 || posOfFigur [i].x >= SizeX || posOfFigur [i].y >= SizeY) return false;

        else if (Field [posOfFigur [i].y] [posOfFigur [i].x]) return false;
        }

    return true;
    }

//====================================================

void RotateFigure ()
    {
    Point p = posOfFigur [1];

    for (int i = 0; i < 4; i++)
        {
        int x  = posOfFigur [i].y - p.y;
        int y  = posOfFigur [i].x - p.x;

        posOfFigur [i].x =    p.x -   x;
        posOfFigur [i].y =    p.y +   y;
        }

    if (!checkBorder ()) for (int i = 0; i < 4; i++) posOfFigur [i] = oldPosOfFigur [i];
    }
