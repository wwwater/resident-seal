#ifndef SEAL_AI_H
#define SEAL_AI_H

#include "utils.h"
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
    bool wantsToMove();
    bool fianceeDetected(bool approach);
    World *world;
    Seal *seal;
    std::vector<Cell> path;
    Cell goal;
    Seal *goalSeal;
    void createGoal();
    void chooseAnotherSealAsGoal();
    void updateGoalSealLocation();
    int sealStrategy;
    void actAccordingStrategy();
};

#endif //SEAL_AI_H
