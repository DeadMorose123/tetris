

void Button :: dump ()
    {

    printf ("Button { x = %lg, y = %lg, sizeX = %lg, sizeY = %lg, text <%s>, state %i, pic %p }\n", x, y, sizeX, sizeY, text, state, pic);

    }

//=============================================================================
void Button :: draw ()
    {
    assert (pic);
    txAlphaBlend (txDC (), x, y, sizeX, sizeY, pic);

    }
//=============================================================================
int Button :: check ()
    {

    if (x       < txMouseX() && y       < txMouseY() &&
        x+sizeX > txMouseX() && y+sizeY > txMouseY())
        {
        state = hovered;

        if (txMouseButtons() == 1)
            {
            state = pressed;
            }
        }
    else
        {
        state = released;
        }
    return state;
    }

