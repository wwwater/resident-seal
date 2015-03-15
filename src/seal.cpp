#include "seal.h"
#include "world.h"
#include "fog.h"
#include "utils.h"

Seal::Seal(World *world, int row, int col, int direction) : 
    MovingObject(float(col + 0.5), float(row + 0.5), direction)
{
    this->isMoving = false;
    this->cooldown         = 0;
    this->cooldownDuration = 30;
    this->fatigue          = 0;
    this->maxFatigue       = randint(550, 650);
    this->fatigueRate      = randint(1, 5);
    this->recoveryRate     = randint(1, 3);

    this->world = world;
    this->ai = new SealAI(this->world, this);
}

bool Seal::isAtCellCenter()
{
    return fabs(this->x - floor(this->x) - 0.5) <= 0.5 * this->stepSize &&
           fabs(this->y - floor(this->y) - 0.5) <= 0.5 * this->stepSize;
}

void Seal::advance()
{
    // 1. Seal gets tired from walking. Update fatigue and cooldown.
    this->fatigue = this->isMoving ?
        this->fatigue + this->fatigueRate :
        std::max(0, this->fatigue - this->recoveryRate);
    this->cooldown = std::max(0, this->cooldown - 1);

    // 2. Making a decision
    if (this->isAtCellCenter() && this->cooldown == 0) {
        if (this->isMoving) {
            // It always stops upon reaching the center of a cell to make sure
            // the path ahead is clear.
            this->x = floor(this->x) + 0.5;
            this->y = floor(this->y) + 0.5;
        }

        SealAction action = this->ai->getAction();
        if (action == SealAction::noop) {
            this->cooldown = this->isMoving ? this->cooldownDuration : 0;
        } else if (action == SealAction::left) {
            this->rotate(-1);
            this->cooldown = this->cooldownDuration;
            action = this->ai->getAction();
        } else if (action == SealAction::right) {
            this->rotate(1);
            this->cooldown = this->cooldownDuration;
            action = this->ai->getAction();
        }

        bool wayIsClear = this->canStepOn(this->cellAhead());

        if (action == SealAction::go && this->fatigue < this->maxFatigue
                                     && wayIsClear) {
            this->isMoving = true;
            this->cooldown = 0;
            this->world->putSealAt(this, this->cellAhead());
        } else {
            this->isMoving = false;
        }
    }

    // 3. Process results
    if(this->isMoving) {
        Cell cellBeforeMovement = this->cell();
        this->x += this->stepSize * this->dx();
        this->y += this->stepSize * this->dy();
        // When crossing into a new cell, free the current one.
        // The new cell is already reserved by this seal.
        if (this->cell() != cellBeforeMovement) {
            this->world->putSealAt(NULL, cellBeforeMovement);
        }
    }

    this->clearFog();
}

void Seal::clearFog()
{
    this->world->fog->clearTile(this->cell());
}

bool Seal::canStepOn(Cell cell)
{
    return (!this->world->hasObstacleAt(cell)
        && !this->world->hasSealAt(cell));
}
