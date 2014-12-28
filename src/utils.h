class Direction
{
public:
    static float x(int dir);
    static float y(int dir);
    static int intX(int dir);
    static int intY(int dir);
    static int rotate(int dir, int turns);
};

int randint(int min, int max);