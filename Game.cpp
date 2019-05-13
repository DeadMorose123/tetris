#include "TXLib.h"

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
void StepPlayGame (bool cheatMode);
void DrawPlayGame (HDC tiles, HDC background);
void CheakIsLineReady ();
int PlayGame(HDC tiles, HDC background, bool cheatMode);
void CreatNewFigure (bool cheatMode);
void PrintScore ();

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

int n = rand() % 6;;
int colorNum = 1 + rand() % 7;

int NLine = 0;

int PlayGame (HDC tiles, HDC background, bool cheatMode)
    {

    //printf ("%i\n", checkBorder());
    txBegin ();

    aKeyBoardControl Player = {'A', 'W', 'D', 'S'};

    CreatNewFigure (cheatMode);

    while (checkBorder())
        {

        keyBoardControl (Player);

        StepPlayGame(cheatMode);

        CheakIsLineReady ();

        DrawPlayGame (tiles, background);

        PrintScore ();

        txSleep (100);
        }

    for (int y = 0; y < SizeY; y++)
        for (int x = 0; x < SizeX; x++)
            Field [y][x] = 0;

    NLine = 0;

    return 0;
    }
//====================================================

void PrintScore ()
    {
    char lines [10] = "";
    sprintf (lines, "%i", NLine*10);
    txSetColor (TX_BLACK);
    txSelectFont ("Impact", 150);
    txDrawText (621, 585, 799, 736, lines);
    }

//====================================================

void CreatNewFigure (bool cheatMode)
    {
    if (cheatMode) n = 0;

    else n = rand() % 6;

    //printf ("%i", n);

    colorNum = 1 + rand() % 7;

    for (int i = 0; i < 4; i++)
        {
        posOfFigur[i].x = Figures[n][i] % 2 + SizeX / 2;

        posOfFigur[i].y = Figures[n][i] / 2;
        }
    }

//====================================================

void CheakIsLineReady ()
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
		else NLine ++;
        }
     }

//====================================================

void DrawPlayGame (HDC tiles, HDC background)   // DrawField
    {
    txBitBlt (0, 0, background);

    for (int i = 0; i < SizeY; i++)   // TODO change i to y; j to x
        for (int j = 0; j < SizeX; j++)
            {
            //printf ("%i", Field[i][j]);

            if (Field[i][j] == 0) continue;

            txBitBlt (txDC (), j*SizeTile + WField, i*SizeTile, SizeTile, SizeTile, tiles, Field [i][j] * SizeTile, 0);
            }

    for (int i = 0; i < 4; i++)
        {
        //printf ("x %i, y %i\n", posOfFigur [i].x, posOfFigur [i].y);

        txBitBlt (txDC (), posOfFigur [i].x * SizeTile + WField, posOfFigur [i].y * SizeTile, SizeTile, SizeTile, tiles, colorNum * SizeTile, 0);
        }

    //printf ("\n");
    }

//====================================================

void StepPlayGame (bool cheatMode)   // UpdatePlayGame
    {
    for (int i = 0; i < 4; i++)
        {
        oldPosOfFigur [i] = posOfFigur [i];

        posOfFigur [i].y += 1;
        }

    if (!checkBorder ())
        {
        for (int i = 0; i < 4; i++) {Field [oldPosOfFigur[i].y][oldPosOfFigur[i].x] = colorNum;}

        CreatNewFigure (cheatMode);
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
