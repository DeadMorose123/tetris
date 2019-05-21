

const int MaxLenWord = 50;

class Button
    {
    public:
        enum state_t {released, hovered, pressed};

        double x, y, sizeX, sizeY;
        char text [MaxLenWord];
        state_t state;
        HDC pic;

        void draw ();
        int check ();
        void dump ();
    };

