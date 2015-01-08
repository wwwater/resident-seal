#include "seal.h"
#include "world.h"
#include "fog.h"
#include "utils.h"

Seal::Seal(World *world, int row, int col, int direction)
{
    this->x = col + 0.5;
    this->y = row + 0.5;
    this->direction = direction;
    this->isMoving = false;

    this->fatigue      = 0;
    this->maxFatigue   = randint(550, 650);
    this->fatigueRate  = randint(1, 5);
    this->recoveryRate = randint(1, 5);
    
    this->world = world;
    this->ai = new SealAI(this->world, this);
}

bool Seal::isAtCellCenter()
{
    return std::abs(this->x - floor(this->x) - 0.5) <= 0.5 * this->stepSize &&
           std::abs(this->y - floor(this->y) - 0.5) <= 0.5 * this->stepSize;
}

void Seal::advance()
{
    // 1. Fatigue change
    // Seal gets tired from walking.
    this->fatigue = this->isMoving ?
        this->fatigue + this->fatigueRate :
        std::max(0, this->fatigue - this->recoveryRate);
    
    bool wasMoving = this->isMoving;
    int currentRow = floor(this->y);
    int currentCol = floor(this->x);
    
    int rowAhead = currentRow + Direction::intY(this->direction);
    int colAhead = currentCol + Direction::intX(this->direction);
   
    // 2. At cell centre -> continue / stay
    if (this->isAtCellCenter()) {
        if (this->isMoving) {
            // It always stops upon reaching the center of a cell to make sure
            // the path ahead is clear.
            this->isMoving = false;
            this->x = floor(this->x) + 0.5;
            this->y = floor(this->y) + 0.5;
        }
        bool approachGoal = false;
        bool onMission = this->ai->hasGoal(approachGoal);
        
        if (!onMission || !wasMoving) {
            // She can decide to change her direction
            this->direction = this->ai->newDirection();
            rowAhead = currentRow + Direction::intY(this->direction);
            colAhead = currentCol + Direction::intX(this->direction);
        }

        bool wayIsClear = !this->world->hasSealAt(rowAhead, colAhead) &&
                          !this->world->hasObstacleAt(rowAhead, colAhead);
        if (wayIsClear) {
            if (onMission) {
                this->isMoving = true;
            } else {
                this->isMoving = this->ai->wantsToMove(wasMoving); 
            } 
        }
        if(this->isMoving) {
            this->world->putSealAt(this, rowAhead, colAhead);
        }
    }

    
    // 3. Process results
    if(this->isMoving) {   
        this->x += this->stepSize * Direction::x(this->direction);
        this->y += this->stepSize * Direction::y(this->direction);

        // When crossing into a new cell, free the current one.
        // The new cell is already reserved by this seal.
        if (floor(this->y) != currentRow || floor(this->x) != currentCol) {
            this->world->putSealAt(NULL, currentRow, currentCol);
        }
    }

    this->clearFog();
}

void Seal::clearFog()
{
    this->world->fog->clearTile(floor(this->y), floor(this->x));
}
