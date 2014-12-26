#ifndef SEAL_H
#define SEAL_H

#include <QtGlobal>

class Seal
{
public:
    float x;
    float y;
    int direction; // [0.. 7]

    Seal(int row, int col, int direction);
    void advance();

private:
    bool isMoving = false;
    float stepSize = 1 / 600;
};

#endif // SEAL_H
