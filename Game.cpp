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
    {
    int x, y;
    };

struct RunGamePar
    {
    HDC tiles;
    HDC background;
    bool cheatMode;
    Point position;
    aKeyBoardControl Player;
    };

void keyBoardControl (int Field[SizeY][SizeX], const aKeyBoardControl theControl, Point posOfFigur[]);
bool checkBorder (int Field[SizeY][SizeX], Point posOfFigur []);
void RotateFigure (int Field[SizeY][SizeX], Point posOfFigur []);
void StepPlayGame (int Field[SizeY][SizeX], bool cheatMode, int* ColorNum, int* NumBrick, int* newColorNum, int* newNumBrick, Point posOfFigur[]);
void DrawField (int Field[SizeY][SizeX], HDC tiles, HDC background, int ColorNum, Point posOfFigur[], Point position);
void CheakIsLineReady (int Field[SizeY][SizeX], int* NLines);
int RunGame (RunGamePar* game);
void CreatNewFigure (bool cheatMode, int* NumBrick,  int* newNumBrick, int* newColorNum, Point posOfFigur[]);
void copyArray (Point oldArr [], Point newArr [], int lenArr);

void PrintScore (int NLines);
void PrintTime (int timer);
void PrintNextFigur (HDC tiles, int newNumBrick, int newColorNum, Point position);

int RunLevels (bool cheatMode);
int Level1 (bool cheatMode);
int Level2 (bool cheatMode);

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

int RunLevels (bool cheatMode)
    {
    int     ok = Level1 (cheatMode);
    //if (ok) ok += Level2 (cheatMode);
    //if (ok) ok = Level3 (cheatMode);


    std :: cout << ok;
    return ok;
    }

//====================================================

int Level1 (bool cheatMode)
    {
    RunGamePar game1 = {Resourses[tiles].pic, Resourses[Tetris].pic, cheatMode, {0, 0}, {'A', 'W', 'D', 'S'}};

   // _beginthread (RunGame, 0, &game1,

    return RunGame (&game1);

    }

//====================================================

/*int Level2 (bool cheatMode)
    {


    _beginthread (RunGame, 0,

    int Score = RunGame (Resourses[tiles].pic, Resourses[Tetris].pic, cheatMode, {0, 0}, {'A', 'W', 'D', 'S'});
    Score += RunGame (Resourses[tiles].pic, Resourses[Tetris].pic, cheatMode, {870, 1023}, {VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN});

    return Score;
    }       */

//====================================================
int RunGame (RunGamePar* game)
    {

    HDC              tiles      = game -> tiles;
    HDC              background = game -> background;
    bool             cheatMode  = game -> cheatMode;
    Point            position   = game -> position;
    aKeyBoardControl Player     = game -> Player;

    int Field[SizeY][SizeX] = {0};

    int newNumBrick = rand() % 6;
    int NumBrick = rand() % 6;

    int newColorNum = 1 + rand() % 7;
    int ColorNum = 1 + rand() % 7;

    int NLines = 0;

    int timer = GetTickCount ();

    Point posOfFigur[4] = {};
    txBegin ();

    CreatNewFigure (cheatMode, &NumBrick, &newNumBrick, &newColorNum, posOfFigur);

    txPlaySound ("music.wav", SND_LOOP);


    while (checkBorder(Field, posOfFigur))
        {

        StepPlayGame(Field, cheatMode, &ColorNum, &NumBrick, &newColorNum, &newNumBrick, posOfFigur);

        keyBoardControl (Field, Player, posOfFigur);

        CheakIsLineReady (Field, &NLines);

        DrawField (Field, tiles, background, ColorNum, posOfFigur, position);

        PrintScore (NLines);

        PrintTime (timer);

        PrintNextFigur (tiles, newNumBrick, newColorNum, position);

        txSleep (100);
        }

    PrintTime(timer);
    txPlaySound (NULL);

    return NLines * 10;
    }

//====================================================

void PrintNextFigur (HDC tiles, int newNumBrick, int newColorNum, Point position)
    {
    Point posOfFigur[4] = {};

    for (int i = 0; i < 4; i++)
        {
        posOfFigur[i].x = Figures[newNumBrick][i] % 2 + SizeX / 2;

        posOfFigur[i].y = Figures[newNumBrick][i] / 2;
        }

    for (int i = 0; i < 4; i++)
        {
        txBitBlt (txDC (), posOfFigur [i].x * 35 + WField + position.x + 420, posOfFigur [i].y * 35 + position.y + 93, SizeTile, SizeTile, tiles, newColorNum * SizeTile, 0);
        }
    }


//====================================================

void PrintTime (int timer)
    {
    timer = (GetTickCount () - timer) / 1000;

    char textOfTime [50] = "";
    unsigned n = sprintf (textOfTime, "%i:%02i", timer/60, timer%60);
    assert (n < sizeof (textOfTime) - 1);

    txSetColor (TX_BLACK);
    txSelectFont ("Impact", 100);
    txDrawText (621, 824, 799, 979, textOfTime);
    }

//====================================================

void PrintScore (int NLines)
    {
    char lines [10] = "";
    sprintf (lines, "%i", NLines*10);

    txSetColor (TX_BLACK);
    txSelectFont ("Impact", 100);
    txDrawText (621, 585, 799, 736, lines);
    }

//====================================================

void CreatNewFigure (bool cheatMode, int* NumBrick, int* newNumBrick, int* newColorNum, Point posOfFigur[])
    {
    if (cheatMode) *NumBrick = 0;

    else *newNumBrick = rand() % 6;

    *newColorNum = 1 + rand() % 7;

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

void DrawField (int Field[SizeY][SizeX], HDC tiles, HDC background, int ColorNum, Point posOfFigur [], Point position)   // DrawField
    {

    txBitBlt (txDC (), position.x, position.y, WndSz.x, WndSz.y, background);

    for (int y = 0; y < SizeY; y++)
        for (int x = 0; x < SizeX; x++)
            {
            if (Field[y][x] == 0) continue;

            txBitBlt (txDC (), x*SizeTile + WField + position.x, y*SizeTile + position.y, SizeTile, SizeTile, tiles, Field [y][x] * SizeTile, 0);
            }

    for (int i = 0; i < 4; i++)
        {
        txBitBlt (txDC (), posOfFigur [i].x * SizeTile + WField + position.x, posOfFigur [i].y * SizeTile + position.y, SizeTile, SizeTile, tiles, ColorNum * SizeTile, 0);
        }
    }

//====================================================

void StepPlayGame (int Field[SizeY][SizeX], bool cheatMode, int* ColorNum, int* NumBrick, int* newColorNum, int* newNumBrick, Point posOfFigur [])
    {
    Point oldPosOfFigur [4] = {0};

    copyArray (oldPosOfFigur, posOfFigur, 4);

    for (int i = 0; i < 4; i++)
        {
        posOfFigur [i].y += 1;
        }

    if (!checkBorder (Field, posOfFigur))
        {
        for (int i = 0; i < 4; i++) {Field [oldPosOfFigur[i].y][oldPosOfFigur[i].x] = *ColorNum;}

        *NumBrick = *newNumBrick;
        *ColorNum = *newColorNum;

        CreatNewFigure (cheatMode, NumBrick, newNumBrick, newColorNum, posOfFigur);
        }
    }

//====================================================

void keyBoardControl (int Field[SizeY][SizeX], const aKeyBoardControl theControl, Point posOfFigur[])
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
        RotateFigure (Field, posOfFigur);
        txSleep (10);
        }

    for (int i = 0; i < 4; i++) { oldPosOfFigur [i] = posOfFigur [i]; posOfFigur [i].x += dx; }

    if (!checkBorder (Field, posOfFigur))
        for (int i = 0; i < 4; i++) posOfFigur [i] = oldPosOfFigur [i];
    }

//====================================================

bool checkBorder (int Field[SizeY][SizeX], Point posOfFigur[])
    {
    for (int i = 0; i < 4; i++)
        {
        if (posOfFigur [i].x < 0 || posOfFigur [i].x >= SizeX || posOfFigur [i].y >= SizeY) return false;

        else if (Field [posOfFigur [i].y] [posOfFigur [i].x]) return false;
        }

    return true;
    }

//====================================================

void RotateFigure (int Field[SizeY][SizeX], Point posOfFigur[])
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

    if (!checkBorder (Field, posOfFigur)) for (int i = 0; i < 4; i++) posOfFigur [i] = oldPosOfFigur [i];
    }

//====================================================

void copyArray (Point oldArr [], Point newArr [], int lenArr)
    {
    for (int i = 0; i < lenArr; i++) {oldArr [i] = newArr [i];}
    }
