

//=============================================================================
void Button :: draw ()
    {
    txAlphaBlend (txDC (), x, y, x+sizeX, y+sizeY, pic);

    }
//=============================================================================
int Button :: check ()
    {
    state_t oldState = state;

    if (x       < txMouseX() && y       < txMouseY() &&
        x+sizeX > txMouseX() && x+sizeY > txMouseY())
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

