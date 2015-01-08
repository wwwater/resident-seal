#include "seal_AI.h"
#include "utils.h"
#include "world.h"

SealAI::SealAI(World *world, Seal *seal): world(world), seal(seal)
{
}

bool SealAI::wantsToMove(bool wasMoving)
{
    if (wasMoving) { // If it was moving and isn't too tired, it may decide to keep going.
        return randint(0, this->seal->maxFatigue) > this->seal->fatigue;
    } else if (this->seal->fatigue == 0) {  // He may also start going after he is completely recovered.
        return randint(0, this->seal->maxFatigue) == 0;
    }
    return false;
} 

int SealAI::newDirection()
{ 
    if (randint(0, 999) == 0) { 
        return Direction::rotate(this->seal->direction, randint(-1, 1));
    }
    return this->seal->direction;
}

bool SealAI::fianceeDetected()
{
    bool fianceeDetected = false;
    int dirX = Direction::intX(this->seal->direction);
    int dirY = Direction::intY(this->seal->direction);
    int nextCol = int(this->seal->x) + dirX; 
    int nextRow = int(this->seal->y) + dirY; 
    while (true) {
        nextCol += dirX;
        nextRow += dirY;
        if (!this->world->hasObstacleAt(nextRow, nextCol)) { // there is no obstacle
            if (this->world->hasSealAt(nextRow, nextCol)) { //there is another seal
                int anotherSealDirection = this->world->getSealAt(nextRow, nextCol)->direction;  
                if (std::abs(this->seal->direction - anotherSealDirection) != 400) { //that seal is looking at me
                    fianceeDetected = true;    
                }
                break;
            }
        } else {
            break;
        }
    }
    return fianceeDetected;
}

bool SealAI::continueInThisDirection()
{
    return (this->fianceeDetected());
}
