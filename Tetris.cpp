#include "TXLib.h"
#include <cstring>
#include "Button.h"

const POINT WndSize = {870, 1023};

enum idButtons {idGame, idOptions, idAchievements, idLeaderboards, idTutorial};

HDC loadDC(char *nameOfPic, HDC picture);
bool checkButton (double x1,double y1,double x2,double y2);
void startGame (HDC game);
void startMenu (HDC menu, HDC game, HDC tetromino);

void drawMenu (Button menu []);

#define END  {}

int main ()
    {
    txCreateWindow (WndSize.x, WndSize.y);

    Button menu[] = {{561, 205, 255, 92, "Game"             , idGame        },
                     {561, 316, 255, 92, "Options"          , idOptions     },
                     {561, 427, 255, 92, "Achievements"     , idAchievements},
                     {561, 538, 255, 92, "Leaderboards"     , idLeaderboards},
                     {561, 649, 255, 92, "Tutorial and help", idTutorial    },
                     END                                                     };
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        drawMenu (menu);


        for (int i = 0; ROUND(menu[i].sizeX); i++)
            {
            menu[i].check();

            menu[i].checkStates();

            }
        }

    /*char nameOfMenu[5] = "menu";
    char nameOfGame[5] = "game";
    char nameOfTetromino[10] = "tetromino";

    HDC menu = loadDC (nameOfMenu, menu);
    HDC game = loadDC (nameOfGame, game);
    HDC tetromino = loadDC (nameOfTetromino, tetromino);

    startMenu (menu, game, tetromino);

    txDeleteDC (menu);
    txDeleteDC (game);
    txDeleteDC (tetromino);*/

    return 0;
    }
//=============================================================================
void drawMenu (Button menu [])
        {
        for (int i = 0; ROUND(menu[i].sizeX); i++)
            {
            menu[i].draw();
            }
        }

//=============================================================================
void startGame (HDC game)
        {
        txAlphaBlend (txDC(), 0, 0, WndSize.x, WndSize.y, game);

        }
//=============================================================================
void startMenu (HDC menu, HDC game, HDC tetromino)
    {
    txBitBlt (txDC(), 0, 0, WndSize.x, WndSize.y, menu);


    }
//=============================================================================
HDC loadDC (char *nameOfPic, HDC picture)   // TODO move to the Button.h
    {

    char url[50] = "Images\\";
    strcat (url, nameOfPic);
    strcat (url, ".bmp");

    picture = txLoadImage (url);

    char check[50] = "I can't load background from ";
    strcat (check, url);
    if (!picture) txMessageBox (check);

    return picture;

    }

