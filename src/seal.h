#ifndef SEAL_H
#define SEAL_H

#include <QtGlobal>

class World;
class Seal
{
public:
    float x;
    float y;
    int direction; // [0.. 7]
    World *world;

    Seal(int row, int col, int direction);
    void advance();
    bool isAtCellCenter();

private:
    float stepSize = 1.0 / 60.0;
    bool isMoving = false;
    int tiredness;
    int maxTiredness; //these 4 should be const, be the consts must be inilialized in the list before constructor body. But it looks too cumbersome then.
    int minTiredness;
    int rateTiredness;
    int rateRecovery;
};

#endif // SEAL_H
