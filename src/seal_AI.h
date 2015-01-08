#ifndef SEAL_AI_H
#define SEAL_AI_H

class World;
class Seal;
class SealAI
{
public:
    SealAI(World *world, Seal *seal);
    bool wantsToMove(bool wasMoving);
    int newDirection();
    bool fianceeDetected();
    bool continueInThisDirection(); 
    World *world;
    Seal *seal;
};

#endif //SEAL_AI_H
