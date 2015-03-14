#ifndef SEAL_AI_H
#define SEAL_AI_H

#include <vector>

class World;
class Seal;
enum class SealAction;
class SealAI
{
public:
    SealAI(World *world, Seal *seal);
    SealAction getAction();
private:
    bool wantsToMove(bool wasMoving);
    int newDirection();
    bool fianceeDetected(bool approach);
    bool hasGoal(bool approach); 
    World *world;
    Seal *seal;
    int pathToGoal();
    std::vector<int> path;
    int rowGoal;
    int colGoal;
    void createGoal();
};

#endif //SEAL_AI_H
