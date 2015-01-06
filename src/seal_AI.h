#ifndef SEAL_AI_H
#define SEAL_AI_H

class World;
class SealAI
{
public:
    SealAI(World *world);
    bool wantsToMove(bool wasMoving, int fatigue, int maxFatigue);
    int newDirection(int oldDirection);
    bool fianceeDetected(int row, int col, int direction);
    World *world;
};

#endif //SEAL_AI_H
