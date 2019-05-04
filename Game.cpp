#include "TXLib.h"
#include <cstring>

const POINT WndSize = {870, 1023};

#include "Button.h"
#include "Button.cpp"

#include "Resourse.h"
#include "Resourse.cpp"

bool checkBgutton (double x1,double y1,double x2,double y2);
void drawButtons (Button ButMenu[]);
void start (Resourse Resourses []);
std :: pair <int, Button :: state_t> drawMenu (Button ButMenu []);
void loadResourses (Resourse Resourses[]);
void deleteResourses (Resourse Resourses[]);
void loadButtons (Resourse Resourses[], Button ButMenu[]);
void checkButtons (Button ButMenu[]);

#define END  {}
#define debug printf("= %d  \n", __LINE__)

int main ()
    {
    _txConsoleMode = SW_SHOW;
    txBegin ();
    txCreateWindow (WndSize.x, WndSize.y);

    Button ButMenu[] = {{  0,   0,   0,  0, "Framework"        },  // 0
                        {561, 205, 255, 92, "Game"             },  // 1
                        {561, 316, 255, 92, "Options"          },  // 2
                        {561, 427, 255, 92, "Achievements"     },  // 3
                        {561, 538, 255, 92, "Leaderboards"     },  // 4
                        {561, 649, 255, 92, "Tutorial and help"},  // 5
                        END                                     };

    Resourse Resourses[] = {{"Game"            }, // 0
                           {"Options"          }, // 1
                           {"Achievements"     }, // 2
                           {"Leaderboards"     }, // 3
                           {"Tutorial and help"}, // 4
                           {"Menu"             }, // 5
                           {"Tetris"           }, // 6
                           {"Tetromino"        }, // 7
                           {"Framework"        }, // 8
                           END                  };

    loadResourses (Resourses);
    loadButtons (Resourses, ButMenu);

    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        start (Resourses);
        //auto state = drawMenu (ButMenu);
        //printf ("button %i, state %i\n", state.first, state.second);

        txSleep (50);
        }
    deleteResourses (Resourses);
    return 0;
    }
//=============================================================================
std :: pair <int, Button :: state_t> drawMenu (Button ButMenu [])
        {
        for (int i = 1; ROUND(ButMenu[i].sizeX); i++)
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

                return std :: pair <int, Button :: state_t> (i, Button :: hovered);
                }
            else if (state == 2)
                {
                return std :: pair <int, Button :: state_t> (i, Button :: pressed);
                }
            }

        return std :: pair <int, Button :: state_t> (0, Button :: released);
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
