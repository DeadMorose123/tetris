#include "include.h"

void changeX (void*);

int X = 0;
CRITICAL_SECTION LockX = {};

int main ()
    {
    InitializeCriticalSection (&LockX);

    _beginthread (changeX, 0, nullptr);

    for (;;)
        {
        EnterCriticalSection (&LockX);
        printf ("%i\n", X);
        LeaveCriticalSection (&LockX);

        Sleep (10);
        }

    DeleteCriticalSection (&LockX);

    }

void changeX (void*)
    {
    while (true)
        {
        EnterCriticalSection (&LockX);
        if (++X > 9) X = 0;
        LeaveCriticalSection (&LockX);

        Sleep (10);
        }
    }
