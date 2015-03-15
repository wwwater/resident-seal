#include "seal_AI.h"
#include "world.h"

SealAI::SealAI(World *world, Seal *seal) : 
    world(world),
    seal(seal),
    goal(this->seal->cell()),
    sealStrategy(1)
{
}

SealAction SealAI::getAction()
{
    if (this->wantsToMove()) {
        if (this->seal->cell() == this->goal) {
            if (this->seal->fatigue > 0) {
                return SealAction::noop;
            } else {
                this->actAccordingStrategy();
            }
        }
        if (this->path.size() > 0) {
            Cell nextCell = this->path.back();
            if (this->world->hasSealAt(nextCell)) {
                for (auto cell: path) {
                    this->world->debug->clearMarkerAt(cell);
                }
                this->path.clear();
                return SealAction::noop;
            } else {
                int turn = this->seal->turnDirectionTo(nextCell);
                    if (turn == 0) { // Follow the path
                    this->path.pop_back();
                    return SealAction::go;
                } else if (turn == 1) { // Rotate to face the path direction.
                    return SealAction::right;
                }
                return SealAction::left;
            }
        } else { 
            this->path = Algorithms::pathToGoal(
                this->world->height, this->world->width,
                this->seal->cell(),
                this->goal,
                [this](Cell cell) {
                    return this->world->hasObstacleAt(cell) ||
                           this->world->hasSealAt(cell);
                }
            );
            for (auto cell: path) {
                this->world->debug->addMarkerAt(cell);
            }
            return SealAction::noop;
        }
    }
    return SealAction::noop;
}

bool SealAI::wantsToMove()
{
    if (this->seal->isMoving) {
        // If it was moving and isn't too tired, it may decide to keep going.
        return randint(0, this->seal->maxFatigue) > this->seal->fatigue;
    } else if (this->seal->fatigue == 0) {
        // He may also start going after he is completely recovered.
        return randint(0, this->seal->maxFatigue) == 0;
    }
    return false;
} 
/*
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
                int anotherSealDirection =
                    this->world->getSealAt(nextRow, nextCol)->direction;  
                //that seal is looking at me
                if (std::abs(this->seal->direction - anotherSealDirection) != 400) {
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
}*/

void SealAI::createGoal()
{
    int rows = this->world->height;
    int cols = this->world->width;
    std::vector<Cell> availableCells;
    for (int row = 0; row < rows; ++ row) {
        for (int col = 0; col < cols; ++col) {
            if (this->seal->canStepOn(Cell(row, col))) {
                availableCells.push_back(Cell(row, col));
            }    
        }
    }
    this->goal = availableCells[qrand() % availableCells.size()];   
    return;
}

void SealAI::chooseAnotherSealAsGoal()
{
    int nSeals = this->world->seals->size();
    this->goalSeal = (this->world->seals->at(qrand() % nSeals));
}

void SealAI::updateGoalSealLocation()
{
    this->goal = this->goalSeal->cell();
}

void SealAI::actAccordingStrategy()
{
    if (sealStrategy == 0) {
        this->createGoal();
    } else if (sealStrategy == 1) {
        this->chooseAnotherSealAsGoal();
        this->updateGoalSealLocation();
    }
}
