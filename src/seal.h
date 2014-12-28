#ifndef SEAL_H
#define SEAL_H

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
    int fatigue;
    int maxFatigue;
    int fatigueRate;
    int recoveryRate;
};

#endif // SEAL_H
