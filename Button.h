const int MaxLenWord = 20;

class Button
    {
    public:
    enum state_t {released, hovered, pressed};

    double x, y, sizeX, sizeY;
    char text[MaxLenWord];
    int id;
    state_t state;

    void draw ();
    int check();
    void checkStates();
    };
//=============================================================================
void Button :: draw ()
    {
    txSetFillColor (RGB (255, 255, 255));
    txSetColor (TX_GREEN);
    Win32 :: RoundRect (txDC(), ROUND(x), ROUND(y), ROUND(x+sizeX), ROUND(y+sizeY), ROUND(x/10), ROUND(x/10));

    txSetColor (TX_BLUE);
    txDrawText (ROUND(x), ROUND(y), ROUND(x+sizeX), ROUND(y+sizeY), text);

    }
//=============================================================================
int Button :: check ()
    {
    state_t oldState = state;

    if (x < txMouseX() && y < txMouseY() && x+sizeX > txMouseX() && y+sizeY > txMouseY())
        {
        state = hovered;
        return 1;
        if (txMouseButtons() == 1)
            {
            state = pressed;
            }

        }
    else
        {
        state = released;
        return 0;
        }

    if (oldState == 2)
        {
        return 2;

        }
    }
//=============================================================================
void Button :: checkStates()
    {
    printf("button = [%d] %s %d \n", id, text, state);
    }
