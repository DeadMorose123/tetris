//=============================================================================

HDC loadDC (char *nameOfPic)
    {
    char url[MaxLenWord * 2] = "Images\\";
    strncat (url, nameOfPic, sizeof(url)-1);
    strncat (url, ".bmp", sizeof(url)-1);

    HDC picture = txLoadImage (url);

    //printf ("name <%s>, picture %p\n", url, picture);

    char check[MaxLenWord * 2] = "I can't load picture from ";
    strncat (check, url, sizeof(check)-1);
    if (!picture) txMessageBox (check);

    //txBitBlt (txDC (), 100, 100, 0, 0, picture);
    return picture;
    }

//=============================================================================
