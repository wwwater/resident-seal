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

    this->cooldown         = 0;
    this->cooldownDuration = 30;
    this->fatigue          = 0;
    this->maxFatigue       = randint(550, 650);
    this->fatigueRate      = randint(1, 5);
    this->recoveryRate     = randint(1, 5);

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

    bool wasMoving = this->isMoving;
    int rowCurrent = floor(this->y);
    int colCurrent = floor(this->x);

    // 2. Making a decision
    if (this->isAtCellCenter() && this->cooldown == 0) {
        if (this->isMoving) {
            // It always stops upon reaching the center of a cell to make sure
            // the path ahead is clear.
            this->isMoving = false;
            this->x = floor(this->x) + 0.5;
            this->y = floor(this->y) + 0.5;
        }

        SealAction action = this->ai->getAction();
        if (action == SealAction::noop) {
            this->cooldown = wasMoving ? this->cooldownDuration : 0;
        } else if (action == SealAction::left) {
            this->direction = Direction::rotate(this->direction, -1);
            this->cooldown = this->cooldownDuration;
            action = this->ai->getAction();
        } else if (action == SealAction::right) {
            this->direction = Direction::rotate(this->direction, 1);
            this->cooldown = this->cooldownDuration;
            action = this->ai->getAction();
        }

        int rowAhead = rowCurrent + Direction::intY(this->direction);
        int colAhead = colCurrent + Direction::intX(this->direction);
        bool wayIsClear = !this->world->hasSealAt(rowAhead, colAhead) &&
                          !this->world->hasObstacleAt(rowAhead, colAhead);

        if (action == SealAction::go && this->fatigue < this->maxFatigue
                                     && wayIsClear) {
            this->isMoving = true;
            this->cooldown = 0;
            this->world->putSealAt(this, rowAhead, colAhead);
        }
    }

    // 3. Process results
    if(this->isMoving) {
        this->x += this->stepSize * Direction::x(this->direction);
        this->y += this->stepSize * Direction::y(this->direction);

        // When crossing into a new cell, free the current one.
        // The new cell is already reserved by this seal.
        if (floor(this->y) != rowCurrent || floor(this->x) != colCurrent) {
            this->world->putSealAt(NULL, rowCurrent, colCurrent);
        }
    }

    this->clearFog();
}

void Seal::clearFog()
{
    this->world->fog->clearTile(floor(this->y), floor(this->x));
}
