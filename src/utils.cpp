#include <QtGlobal>
#include "utils.h"

float Direction::x(int dir)
{
    switch (dir) {
        case 1:
        case 3:
            return 0.7071067811865476;
        case 5:
        case 7:
            return -0.7071067811865476;
        case 2:
            return 1;
        case 6:
            return -1;
        default:
            return 0;
    }
}

float Direction::y(int dir)
{
    return x((dir + 6) % 8);
}

int Direction::intX(int dir)
{
    return round(x(dir));
}

int Direction::intY(int dir)
{
    return round(y(dir));
}

int Direction::rotate(int dir, int turns)
{
    dir = (dir + turns) % 8;
    return dir < 0 ? 7 + dir : dir;
}

int Direction::col(int idx, int cols)
{
    return idx % cols;
}

int Direction::row(int idx, int cols)
{
    return (idx - col(idx, cols)) / cols; 
}

int Direction::direction(int x, int y)
{
    if (x ==  0 && y == -1) return 0;    
    if (x ==  1 && y == -1) return 1;    
    if (x ==  1 && y ==  0) return 2;    
    if (x ==  1 && y ==  1) return 3;    
    if (x ==  0 && y ==  1) return 4;    
    if (x == -1 && y ==  1) return 5;    
    if (x == -1 && y ==  0) return 6;    
    if (x == -1 && y == -1) return 7;
    return 0;
}

int randint(int min, int max)
{
    return min + qrand() % (max + 1 - min);
}
