#ifndef SEAL_AI_H
#define SEAL_AI_H

class World;
class Seal;
enum class SealAction;
class SealAI
{
public:
    SealAI(World *world, Seal *seal);
    SealAction getAction();
    bool wantsToMove(bool wasMoving);
    int newDirection();
    bool fianceeDetected(bool approach);
    bool hasGoal(bool approach); 
    World *world;
    Seal *seal;
    int directionToGoal();
    int rowGoal;
    int colGoal;
    void createGoal();
};

#endif //SEAL_AI_H
