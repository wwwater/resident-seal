#ifndef SEAL_H
#define SEAL_H

#include <QGraphicsItem>

class Seal
{
    private:
        bool isMoving;
        float stepSize = 1/600; 

    public:
        Seal(int, int, int); // x, y, direction
        void advance();
        float x;
        float y;
        int direction; // [0.. 7]
};

#endif
