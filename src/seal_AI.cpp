#include "seal_AI.h"
#include "utils.h"

SealAI::SealAI(World *world, Seal *seal): world(world), seal(seal)
{
    this->rowGoal = int(this->seal->y);
    this->colGoal = int(this->seal->x);
}

SealAction SealAI::getAction()
{
    if ((this->seal->isMoving && (this->seal->fatigue < this->seal->maxFatigue))
            || this->seal->fatigue == 0) {
        if (this->rowGoal == int(this->seal->y)
         && this->colGoal == int(this->seal->x)) {
            if (this->seal->fatigue > 0) return SealAction::noop;
            else this->createGoal();
        }
    
        int direction = Direction::directionToGoal(int(this->seal->y), int(this->seal->x),
                                    this->rowGoal, this->colGoal,
                                    this->world,
                                    [this](int row, int col)
                                    {return (this->world->hasObstacleAt(row, col)
                                          || this->world->hasSealAt(row, col));}
                                    );
        if (this->seal->direction == direction) return SealAction::go;
        else {
            int diff = direction - this->seal->direction;
            if (diff < -4 || (diff >= 0 && diff < 4)) return SealAction::right;
            return SealAction::left;
        }
    }    
    return SealAction::noop;
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

bool SealAI::fianceeDetected(bool approach)
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
                    if (!approach) {
                        this->seal->direction = (this->seal->direction + 4) % 8;
                    }
                }
                break;
            }
        } else {
            break;
        }
    }
    return fianceeDetected;
}

bool SealAI::hasGoal(bool approach)
{
    return (this->fianceeDetected(approach));
}

void SealAI::createGoal()
{
    int rows = this->world->height;
    int cols = this->world->width;
    std::vector<int> availableCells;
    for (int row = 0; row < rows; ++ row) {
        for (int col = 0; col < cols; ++col) {
            if (!this->world->hasObstacleAt(row, col) && !this->world->hasSealAt(row, col)) {
                availableCells.push_back(row * cols + col);
            }    
        }
    }
    int idxGoal = availableCells[qrand() % availableCells.size()];   
    this->rowGoal = Direction::row(idxGoal, cols);
    this->colGoal = Direction::col(idxGoal, cols);
    return;
}
