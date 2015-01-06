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
    this->ai = new SealAI(this->world);
}

bool Seal::isAtCellCenter()
{
    return std::abs(this->x - floor(this->x) - 0.5) <= 0.5 * this->stepSize &&
           std::abs(this->y - floor(this->y) - 0.5) <= 0.5 * this->stepSize;
}

void Seal::advance()
{
    bool wasMoving = this->isMoving;
    int currentRow = floor(this->y);
    int currentCol = floor(this->x);
    int rowAhead = currentRow + Direction::intY(this->direction);
    int colAhead = currentCol + Direction::intX(this->direction);

    // Seal gets tired from walking.
    this->fatigue = this->isMoving ?
        this->fatigue + this->fatigueRate :
        std::max(0, this->fatigue - this->recoveryRate);

    // It always stops upon reaching the center of a cell to make sure
    // the path ahead is clear.
    if (this->isMoving && this->isAtCellCenter()) {
        this->isMoving = false;
        this->x = floor(this->x) + 0.5;
        this->y = floor(this->y) + 0.5;
    }

    if (!this->isMoving) {
        bool wantsToMove = false;
        bool wayIsClear = !this->world->hasSealAt(rowAhead, colAhead) &&
                          !this->world->hasObstacleAt(rowAhead, colAhead);
        bool fianceeDetected = false;
        if (wayIsClear) {
            fianceeDetected = this->ai->fianceeDetected(currentRow, currentCol, this->direction); 
            if (fianceeDetected){
                wantsToMove = true;
            } else {
                wantsToMove = this->ai->wantsToMove(wasMoving, this->fatigue, this->maxFatigue); 
            }
        }
        if (!fianceeDetected) {
            // No matter whether she can or want to go, she still may decide to
            // turn left or right.
            this->direction = this->ai->newDirection(this->direction);
        }
        
        if (wantsToMove && wayIsClear) {
            this->isMoving = true;
            this->world->putSealAt(this, rowAhead, colAhead);
        }
    }

    if (this->isMoving) {
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
