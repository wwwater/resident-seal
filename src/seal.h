#ifndef SEAL_H
#define SEAL_H

#include "seal_AI.h"

class Seal
{
public:
    float x;
    float y;
    int direction; // [0.. 7]
    World *world;

    Seal(World *world, int row, int col, int direction);
    void advance();
    void clearFog();
    bool isAtCellCenter();
    bool isMoving = false;
    int fatigue;
    int maxFatigue;
    int fatigueRate;
    int recoveryRate;

private:
    float stepSize = 1.0 / 60.0;
    SealAI *ai;
};

#endif // SEAL_H
