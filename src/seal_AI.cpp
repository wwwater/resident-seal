#include "seal_AI.h"
#include "utils.h"
#include "world.h"

SealAI::SealAI(World *world, Seal *seal): world(world), seal(seal)
{
    this->rowGoal = int(this->seal->y);
    this->colGoal = int(this->seal->x);
}

SealAction SealAI::getAction()
{
    int col = int(this->seal->x);
    int row = int(this->seal->y);

    bool willBeMoving = wantsToMove(this->seal->isMoving);

    if (willBeMoving) {
        if (row == this->rowGoal && col == this->colGoal) {
            if (this->seal->fatigue > 0) {
                return SealAction::noop;
            } else {
                this->createGoal();
            }
        }
        if (this->path.size() > 0) {
            std::pair<int, int> nextCell = this->path.back();
            int rowNext = nextCell.first;
            int colNext = nextCell.second;
            if (this->world->hasSealAt(rowNext, colNext)) {
                for (auto cell: path) {
                    this->world->debug->clearMarkerAt(cell.first, cell.second);
                }
                this->path.clear();
                return SealAction::noop;
            } else {
                int direction = Direction::direction(
                    colNext - col, rowNext - row);
                int turn = Direction::turnDirection(
                    this->seal->direction, direction);
                if (turn == 0) {
                    // Follow the path
                    this->path.pop_back();
                    return SealAction::go;
                } else if (turn == 1) { // Rotate to face the path direction.
                    return SealAction::right;
                } else {
                    return SealAction::left;
                }
            }
        } else { 
            this->path = Direction::pathToGoal(
                this->world->height, this->world->width,
                row, col,
                this->rowGoal, this->colGoal,
                [this](int row, int col) {
                    return this->world->hasObstacleAt(row, col) ||
                           this->world->hasSealAt(row, col);
                }
            );
            for (auto cell: path) {
                this->world->debug->addMarkerAt(cell.first, cell.second);
            }
            return SealAction::noop;
        }
    }
    return SealAction::noop;
}

bool SealAI::wantsToMove(bool wasMoving)
{
    if (wasMoving) {
        // If it was moving and isn't too tired, it may decide to keep going.
        return randint(0, this->seal->maxFatigue) > this->seal->fatigue;
    } else if (this->seal->fatigue == 0) {
        // He may also start going after he is completely recovered.
        return randint(0, this->seal->maxFatigue) == 0;
    }
    return false;
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
            if (this->seal->canStepOn(row, col)) {
                availableCells.push_back(row * cols + col);
            }    
        }
    }
    int idxGoal = availableCells[qrand() % availableCells.size()];   
    this->rowGoal = Direction::row(idxGoal, cols);
    this->colGoal = Direction::col(idxGoal, cols);
    return;
}
