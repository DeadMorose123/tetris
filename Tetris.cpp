#include "TXLib.h"
#include <cstring>
#include "Button.h"
#include "Resourse.h"

const POINT WndSize = {870, 1023};

enum idButtons {idGame, idOptions, idAchievements, idLeaderboards, idTutorial};

HDC loadDC(char *nameOfPic);
bool checkButton (double x1,double y1,double x2,double y2);
void drawGame (HDC game);
void start (HDC menu);
void deleteDC (HDC pic);
void drawMenu (Button menu []);

#define END  {}

int main ()
    {
    txCreateWindow (WndSize.x, WndSize.y);
    Button Buttons[] = {{561, 205, 255, 92, "Game"             , idGame        },
                        {561, 316, 255, 92, "Options"          , idOptions     },
                        {561, 427, 255, 92, "Achievements"     , idAchievements},
                        {561, 538, 255, 92, "Leaderboards"     , idLeaderboards},
                        {561, 649, 255, 92, "Tutorial and help", idTutorial    },
                        END                                                     };

    Resourse Resourses[] = {{"Game"             },
                           {"Options"          },
                           {"Achievements"     },
                           {"Leaderboards"     },
                           {"Tutorial and help"},
                           {"Menu"             },
                           {"Tetris"           },
                           {"Tetromino"        },
                           {"Framework"        },
                           END                  };


    for (int i = 0; ROUND (Buttons[i].sizeX); i++)
        {
        Buttons[i].picOfButt = loadDC (Buttons[i].text);
        }

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        start (ResMenu);

        for (int i = 0; ROUND (Buttons[i].sizeX); i++)
            {
            Buttons[i].check();
            }

        txSleep (50);
        }

    deleteDC (ResMenu);
    return 0;
    }
//=============================================================================
void drawMenu (Button Buttons [])
        {
        for (int i = 0; ROUND(Buttons[i].sizeX); i++)
            {
            Buttons[i].draw();
            }
        }
//=============================================================================
void start (HDC menu)
    {
    txBitBlt (txDC(), 0, 0, WndSize.x, WndSize.y, menu);


    }
//=============================================================================
void loadResourses (Resourse Resourses[])
    {
    for (int i = 0; Resoutses[i].name[0] == 0; i++)
        {
        Resoutses[i].pic = loadDC (Resoutses[i].name);
        }
    }
//=============================================================================
