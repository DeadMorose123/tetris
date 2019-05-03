#include "TXLib.h"
#include <cstring>

const POINT WndSize = {870, 1023};

#include "Button.h"
#include "Button.cpp"

#include "Resourse.h"
#include "Resourse.cpp"

bool checkButton (double x1,double y1,double x2,double y2);
void drawButtons (Button ButMenu[]);
void start (Resourse Resourses []);
void drawMenu (Button ButMenu []);
void loadResourses (Resourse Resourses[]);
void deleteResourses (Resourse Resourses[]);
void loadButtons (Resourse Resourses[], Button ButMenu[]);

#define END  {}
#define debug printf("%d = \n", __LINE__)

int main ()
    {
    txCreateWindow (WndSize.x, WndSize.y);
    Button ButMenu[] = {{  0,   0,   0,  0, "Framework"        },
                        {561, 205, 255, 92, "Game"             },
                        {561, 316, 255, 92, "Options"          },
                        {561, 427, 255, 92, "Achievements"     },
                        {561, 538, 255, 92, "Leaderboards"     },
                        {561, 649, 255, 92, "Tutorial and help"},
                        END                                     };

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

    loadResourses (Resourses);
    loadButtons (Resourses, ButMenu);

    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        start (Resourses);
        drawMenu (ButMenu);

        txSleep (50);
        }
    deleteResourses (Resourses);
    return 0;
    }
//=============================================================================
void drawMenu (Button ButMenu [])
        {
        for (int i = 0; ROUND(ButMenu[i].sizeX); i++)
            {
            ButMenu[i].draw();
            if (ButMenu[i].check() == 1)
                {
                txAlphaBlend (txDC (), ButMenu[i].x, ButMenu[i].y, ButMenu[i].x+ButMenu[i].sizeX, ButMenu[i].y+ButMenu[i].sizeY, ButMenu[0].pic);
                }
            }
        }
//=============================================================================
void start (Resourse Resourses [])
    {
    for (int i = 0; Resourses[i].name[0] != 0; i++)
        {
        if (strcmp(Resourses[i].name, "Menu") == 0)
            {
            txBitBlt (txDC(), 0, 0, WndSize.x, WndSize.y, Resourses[i].pic);
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
    for (int i = 0; Resourses[i].name[0] != 0; i++)
        {
        txDeleteDC(Resourses[i].pic);
        }
    }
//=============================================================================
void drawButtons (Button ButMenu[])
    {
    for (int i = 0; ROUND(ButMenu[i].sizeX); i++)
        {
        ButMenu[i].draw();
        }
    }

//=============================================================================
void loadButtons (Resourse Resourses[], Button ButMenu[])
    {
    for (int i = 0; Resourses[i].name[0] != 0; i++)
        {
        for (int j = 0; ROUND (ButMenu[i].sizeX); j++)
            {
            if (strcmp(Resourses[i].name, ButMenu[i].text) == 0)
                {
                ButMenu[i].pic = Resourses[i].pic;
                printf("%s = \n", ButMenu[i].text);
                }
            }
        }
    }
