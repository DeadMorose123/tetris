#include "include.h"
#include <cstring>

const POINT WndSz = {870, 1023};

enum ResourseID {GameBut, OptionsBut, AchievementsBut, LeaderboardsBut, ExitBut, Menu, Tetris, tiles, Framework, youLose};

#include "Button.h"
#include "Button.cpp"

#include "Resource.h"
#include "Resource.cpp"

#define END  {}

Resourse Resourses[] = {{"Game"             }, // 0
                        {"Options"          }, // 1
                        {"Achievements"     }, // 2
                        {"Leaderboards"     }, // 3
                        {"Exit"             }, // 4
                        {"Menu"             }, // 5
                        {"Tetris"           }, // 6
                        {"tiles"            }, // 7
                        {"Framework"        }, // 8
                        {"youLose"          }, // 9
                        END                  };

#include "Game.cpp"

void checkButtons (Button ButMenu []);
void loadResourses (Resourse resourses[]);
void deleteResourses (Resourse resourses[]);
void loadButtons (Button ButMenu[]);

void drawMenu (Button ButMenu []);

#define debug printf("= %d  \n", __LINE__)

int main ()
    {
    txDisableAutoPause();
    //_txConsoleMode = SW_SHOW;
    txBegin ();
    txCreateWindow (WndSz.x, WndSz.y);

    Button ButMenu[] = {{  0,   0,   0,  0, "Framework"        },  // 0
                        {561, 205, 255, 92, "Game"             },  // 1
                        {561, 316, 255, 92, "Options"          },  // 2
                        {561, 427, 255, 92, "Achievements"     },  // 3
                        {561, 538, 255, 92, "Leaderboards"     },  // 4
                        {561, 649, 255, 92, "Exit"             },  // 5
                        END                                     };



    loadResourses (Resourses);
    loadButtons (ButMenu);

    while (true)
        {

        drawMenu (ButMenu);
        checkButtons (ButMenu);
        if (ButMenu[5].check () == 2)
            {
            break;
            }
        txSleep (50);
        }
    deleteResourses (Resourses);
    return 0;
    }
//=============================================================================
void checkButtons (Button ButMenu [])
        {

        if (ButMenu[1].check () == 2)
            {
            RunLevels (0);

            txBitBlt (txDC(), 0, 0, 0, 0, Resourses[9].pic);
            txSleep (3000);
            }
        if (GetAsyncKeyState (VK_OEM_3))
            {
            if (strcmp (txInputBox ("Type your cheat code", "CHEAT"), "qwert") == 0)
                {
                RunLevels (1);
                }
            }
        }
//=============================================================================
void drawMenu (Button ButMenu [])
    {
    for (int i = 0; Resourses[i].name[0] != 0; i++)
        {

        if (strcmp(Resourses[i].name, "Menu") == 0)
            {
            txBitBlt (txDC(), 0, 0, WndSz.x, WndSz.y, Resourses[i].pic);
            }
        }

    for (int i = 1; ROUND(ButMenu[i].sizeX); i++)   //buttons
            {
            ButMenu[i].draw();
            }
    for (int i = 1; ROUND(ButMenu[i].sizeX); i++)
        {
        int state = ButMenu[i].check ();

        if (state == 1)
            {
            txAlphaBlend (txDC (), 3+ButMenu[i].x, ButMenu[i].y, 260, 100, ButMenu[0].pic);
            }
        }
    }
//=============================================================================
void loadResourses (Resourse resourses[])
    {
    for (int i = 0; resourses[i].name[0] != 0; i++)
        {
        resourses[i].pic = loadDC (resourses[i].name);
        }
    }
//=============================================================================
void deleteResourses (Resourse resourses[])
    {
    for (int i = 0; resourses[i].name[1] != 0; i++)
        {
        txDeleteDC(resourses[i].pic);
        }
    }
//=============================================================================
void loadButtons (Button ButMenu[])
    {
    for (int i = 0; Resourses[i].name[0] != 0; i++)
        {

        for (int j = 0; ButMenu[j].text[0] != 0; j++)
            {

            if (strcmp(Resourses[i].name, ButMenu[j].text) == 0)
                {
                ButMenu[j].pic = Resourses[i].pic;
                }
            }
        }
    }
