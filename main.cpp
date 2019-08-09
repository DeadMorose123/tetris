#include "include.h"
#include <cstring>

<<<<<<< HEAD
const POINT WndSz = {870*2, 1023};

enum ResourseID {GameBut, OptionsBut, AchievementsBut, LeaderboardsBut, ExitBut, Menu, Tetris, tiles, Framework, youLose};
=======
const POINT WndSize = {870, 1023};
>>>>>>> parent of e58183c... add next fihur

#include "Button.h"
#include "Button.cpp"

#include "Resource.h"
#include "Resource.cpp"

#include "Game.cpp"

void checkButtons (Button ButMenu [],Resourse Resourses[]);
void loadResourses (Resourse Resourses[]);
void deleteResourses (Resourse Resourses[]);
void loadButtons (Resourse Resourses[], Button ButMenu[]);

void drawMenu (Resourse Resourses [], Button ButMenu []);

#define END  {}
#define debug printf("= %d  \n", __LINE__)

int main ()
    {
    InitializeCriticalSection (&LockDesktop);

    txDisableAutoPause();
    //_txConsoleMode = SW_SHOW;
    txBegin ();
    txCreateWindow (WndSize.x, WndSize.y);

    Button ButMenu[] = {{  0,   0,   0,  0, "Framework"        },  // 0
                        {561, 205, 255, 92, "Game"             },  // 1
                        {561, 316, 255, 92, "Options"          },  // 2
                        {561, 427, 255, 92, "Achievements"     },  // 3
                        {561, 538, 255, 92, "Leaderboards"     },  // 4
                        {561, 649, 255, 92, "Exit"             },  // 5
                        END                                     };

<<<<<<< HEAD
=======
    Resourse Resourses[] = {{"Game"            }, // 0
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

>>>>>>> parent of e58183c... add next fihur
    loadResourses (Resourses);
    loadButtons (Resourses, ButMenu);

    while (true)
        {
<<<<<<< HEAD
        drawMenu (ButMenu);
        checkButtons (ButMenu);

=======

        drawMenu (Resourses, ButMenu);
        checkButtons (ButMenu, Resourses);
>>>>>>> parent of e58183c... add next fihur
        if (ButMenu[5].check () == 2)
            {
            break;
            }

        txSleep (50);
        }

    deleteResourses (Resourses);

    DeleteCriticalSection (&LockDesktop);

    return 0;
    }

//=============================================================================
<<<<<<< HEAD

void checkButtons (Button ButMenu [])
=======
//std :: pair <int, Button :: state_t> drawMenu (Button ButMenu [])
void checkButtons (Button ButMenu [], Resourse Resourses [])
>>>>>>> parent of e58183c... add next fihur
        {

        if (ButMenu[1].check () == 2)
            {
<<<<<<< HEAD
            RunGame()
=======
            PlayGame (Resourses [7].pic, Resourses [6].pic, 0);
>>>>>>> parent of e58183c... add next fihur

            txBitBlt (txDC(), 0, 0, 0, 0, Resourses[9].pic);
            txSleep (3000);
            }
        if (GetAsyncKeyState (VK_OEM_3))
            {
            if (strcmp (txInputBox ("Type your cheat code", "CHEAT"), "qwert") == 0)
                {
<<<<<<< HEAD
                RunGame;
=======
                PlayGame (Resourses [7].pic, Resourses [6].pic, 1);
                txBitBlt (txDC(), 0, 0, 0, 0, Resourses[9].pic);
                txSleep (3000);
>>>>>>> parent of e58183c... add next fihur
                }
            }
        }

//=============================================================================
<<<<<<< HEAD

void drawMenu (Button ButMenu [])
=======
void drawMenu (Resourse Resourses [], Button ButMenu [])
>>>>>>> parent of e58183c... add next fihur
    {
    for (int i = 0; Resourses[i].name[0] != 0; i++)
        {

        if (strcmp(Resourses[i].name, "Menu") == 0)
            {
            txBitBlt (txDC(), 0, 0, WndSize.x, WndSize.y, Resourses[i].pic);
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
<<<<<<< HEAD

void loadResourses (Resourse resourses[])
=======
void loadResourses (Resourse Resourses[])
>>>>>>> parent of e58183c... add next fihur
    {
    for (int i = 0; Resourses[i].name[0] != 0; i++)
        {
        Resourses[i].pic = loadDC (Resourses[i].name);
        }
    }
//=============================================================================
void deleteResourses (Resourse Resourses[])
    {
    for (int i = 0; Resourses[i].name[1] != 0; i++)
        {
        txDeleteDC(Resourses[i].pic);
        }
    }
//=============================================================================
void loadButtons (Resourse Resourses[], Button ButMenu[])
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
