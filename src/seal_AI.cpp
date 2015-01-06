#include "seal_AI.h"
#include "utils.h"
#include "world.h"

SealAI::SealAI(World *world): world(world)
{
}

bool SealAI::wantsToMove(bool wasMoving, int fatigue, int maxFatigue)
{
    if (wasMoving) { // If it was moving and isn't too tired, it may decide to keep going.
        return randint(0, maxFatigue) > fatigue;
    } else if (fatigue == 0) {  // He may also start going after he is completely recovered.
        return randint(0, maxFatigue) == 0;
    }
    return false;
} 

int SealAI::newDirection(int oldDirection)
{ 
    if (randint(0, 999) == 0) { 
        return Direction::rotate(oldDirection, randint(-1, 1));
    }
    return oldDirection;
}

bool SealAI::fianceDetected(int row, int col, int direction)
{
    bool fianceDetected = false;
    int dirX = Direction::intX(direction);
    int dirY = Direction::intY(direction);
    int nextCol = col + dirX; 
    int nextRow = row + dirY; 
    while (true) {
        nextCol += dirX;
        nextRow += dirY;
        if (!this->world->hasObstacleAt(nextRow, nextCol)) { // there is no obstacle
            if (this->world->hasSealAt(nextRow, nextCol)) { //there is another seal
                int anotherSealDirection = this->world->getSealAt(nextRow, nextCol)->direction;  
                if (std::abs(direction - anotherSealDirection) == 4) { //that seal is looking at me
                    fianceDetected = true;    
                }
                break;
            }
        } else {
            break;
        }
    }
    return fianceDetected;
}
