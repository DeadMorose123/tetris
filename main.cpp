#include "TXLib.h"
#include <cstring>

const POINT WndSize = {870, 1023};

#include "Button.h"
#include "Button.cpp"

#include "Resourse.h"
#include "Resourse.cpp"

#include "game.cpp"


void checkButtons (Button ButMenu [],Resourse Resourses[]);
void loadResourses (Resourse Resourses[]);
void deleteResourses (Resourse Resourses[]);
void loadButtons (Resourse Resourses[], Button ButMenu[]);

void drawMenu (Resourse Resourses [], Button ButMenu []);

void Options (Resourse Resourses []);
void Achievements (Resourse Resourses []);
void Leaderboards (Resourse Resourses []);
void TutorialAndHelp (Resourse Resourses []);


#define END  {}
#define debug printf("= %d  \n", __LINE__)

int main ()
    {
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

    loadResourses (Resourses);
    loadButtons (Resourses, ButMenu);

    while (true)
        {

        drawMenu (Resourses, ButMenu);
        checkButtons (ButMenu, Resourses);
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
//std :: pair <int, Button :: state_t> drawMenu (Button ButMenu [])
void checkButtons (Button ButMenu [], Resourse Resourses [])
        {

        if (ButMenu[1].check () == 2)
            {
            PlayGame (Resourses [7].pic, Resourses [6].pic, 0);
            txBitBlt (txDC(), 0, 0, 0, 0, Resourses[9].pic);
            txSleep (3000);
            }
        if (ButMenu[4].check () == 2)
            {
            PlayGame (Resourses [7].pic, Resourses [6].pic, 1);
            txBitBlt (txDC(), 0, 0, 0, 0, Resourses[9].pic);
            txSleep (3000);
            }
        }
//=============================================================================
void drawMenu (Resourse Resourses [], Button ButMenu [])
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
        //printf ("state %i\n", state);
        //printf ("i, %i\n", i);

        //printf ("%i = \n", ButMenu[i].check ());

        if (state == 1)
            {
            txAlphaBlend (txDC (), 3+ButMenu[i].x, ButMenu[i].y, 0, 0, ButMenu[0].pic);
            }
        }
    }
//=============================================================================
void loadResourses (Resourse Resourses[])
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
        //printf ("\n" "i %i, name <%s>, pic %p\n", i, Resourses[i].name, Resourses[i].pic);

        for (int j = 0; ButMenu[j].text[0] != 0; j++)
            {
            //printf ("j %i, text <%s>\n", j, ButMenu[j].text);

            if (strcmp(Resourses[i].name, ButMenu[j].text) == 0)
                {
                ButMenu[j].pic = Resourses[i].pic;
                //printf ("name <%s>, text <%s>, pic %p\n", Resourses[i].name, ButMenu[j].text, ButMenu[j].pic);
                }
            }
        }
    }
