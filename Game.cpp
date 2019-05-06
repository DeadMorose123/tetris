#include "TXLib.h"

const int M = 22;
const int N = 12;

struct aKeyBoardControl
    {
    int left, up, right, down;
    };

struct Point
    {int x, y;};

Point posOfFigur[4], oldPosOfFigur[4];

void keyBoardControl (const aKeyBoardControl theControl);
bool check ();
void Rotate ();
void tick ();
void draw (HDC tiles, HDC background);
void checkLines ();
int game(HDC tiles, HDC background);

int field[M][N] = {0};


int figures[7][4] =
    {
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
    };

int n;
int colorNum;

int game (HDC tiles, HDC background)
    {
    //printf ("%i\n", check());
    txBegin ();
    //txCreateWindow (WndSize.x, WndSize.y);

    aKeyBoardControl Player = {'A', 'W', 'D', 'S'};

    while (check())
        {
        keyBoardControl (Player);

        tick();

        checkLines ();

        draw (tiles, background);


        txSleep (100);
        }
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            {
            if (field[i][j] == 0) continue;
            field [i][j] = 0;
            }


    return 0;
    }
//====================================================
void checkLines ()
    {
    int k=M-1;
	for (int i=M-1;i>0;i--)
        {
		int count=0;
		for (int j=0;j<N;j++)
            {
		    if (field[i][j]) count++;
		    field[k][j]=field[i][j];
            }
		if (count<N) k--;
        }
     }
//====================================================
void draw (HDC tiles, HDC background)
    {
    txBitBlt (txDC (), 0, 0, 0, 0, background);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            {
            if (field[i][j] == 0) continue;
            txBitBlt (txDC (), j*45+27, i*45, 45, 45, tiles, field[i][j]*45, 0);
            }
    for (int i = 0; i < 4; i++)
        {
        txBitBlt (txDC (), posOfFigur[i].x*45+27, posOfFigur[i].y*45, 45, 45, tiles, colorNum*45, 0);
        }

    }
//====================================================
void tick ()
    {
    for (int i = 0; i < 4; i++) { oldPosOfFigur[i] = posOfFigur[i]; posOfFigur[i].y += 1; }

    if (!check())
        {
        for (int i = 0; i < 4; i++) {field [oldPosOfFigur[i].y][oldPosOfFigur[i].x] = colorNum;}

        n = rand() % 6;
        colorNum = 1 + rand() % 7;

        for (int i = 0; i < 4; i++)
            {
            posOfFigur[i].x = figures[n][i] % 2;
            posOfFigur[i].y = figures[n][i] / 2;
            }
        }

    }
//====================================================
void keyBoardControl (const aKeyBoardControl theControl)
    {
    int dx = 0;
    if (GetAsyncKeyState (theControl.right))
        {
        dx = 1;
        }

    if (GetAsyncKeyState (theControl.left))
        {
        dx = -1;
        }
    if (GetAsyncKeyState (theControl.up))
        {
        Rotate ();
        }

    for (int i=0;i<4;i++)  { oldPosOfFigur[i]=posOfFigur[i]; posOfFigur[i].x+=dx; }
    if (!check()) for (int i=0;i<4;i++) posOfFigur[i] = oldPosOfFigur[i];
    }
//====================================================
bool check ()
    {
    for (int i = 0; i < 4; i++)
        {
        if (posOfFigur[i].x < 0 || posOfFigur[i].x >= N || posOfFigur[i].y >= M) return false;
            else if (field[posOfFigur[i].y][posOfFigur[i].x]) return false;
        }
    return true;


    }
//====================================================
void Rotate ()
    {
    Point p = posOfFigur[1]; // ����� ��������
    for (int i = 0; i < 4; i++)
        {
        int x  = posOfFigur[i].y - p.y;
        int y  = posOfFigur[i].x - p.x;
        posOfFigur[i].x =    p.x -   x;
        posOfFigur[i].y =    p.y +   y;
        }

    if (!check()) for (int i=0;i<4;i++) posOfFigur[i]=oldPosOfFigur[i];
    }
