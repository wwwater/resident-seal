#ifndef SEAL_H
#define SEAL_H

#include "seal_AI.h"
#include "utils.h"

enum class SealAction { go, noop, left, right };

class Seal : public MovingObject
{
public:
    World *world;
    Seal(World *world, int row, int col, int direction);
    void advance();
    void clearFog();
    bool canStepOn(int row, int col);
    bool isAtCellCenter();
    bool isMoving = false;
    int cooldown;
    int cooldownDuration;
    int fatigue;
    int maxFatigue;
    int fatigueRate;
    int recoveryRate;

private:
    float stepSize = 1.0 / 60.0;
    SealAI *ai;
};

#endif // SEAL_H
