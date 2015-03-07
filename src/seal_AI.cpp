#include "seal_AI.h"
#include "utils.h"
#include "world.h"
#include <map>
#include <set>
#include <iostream>

SealAI::SealAI(World *world, Seal *seal): world(world), seal(seal)
{
    this->rowGoal = int(this->seal->y);
    this->colGoal = int(this->seal->x);
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


int SealAI::directionToGoal() 
{
    int rowGoal = this->rowGoal;
    int colGoal = this->colGoal;
    int rows = this->world->height;
    int cols = this->world->width;
    std::map<int, float> distToCells; //distances to the cells from the starting position
    std::map<int, int> previousCells; //for extraction the path
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!this->world->hasObstacleAt(r, c) && !this->world->hasSealAt(r, c)) {
                distToCells.insert(distToCells.end(),
                    std::pair<int, float>(r * cols + c, rows + cols));
            }
            this->world->debug->clearMarkerAt(r, c); //remove old traces
        }
    }
    int rowStart = int(this->seal->y);
    int colStart = int(this->seal->x);
    int idxStart = rowStart * cols + colStart;
    int idxGoal = rowGoal * cols + colGoal;

    std::set<int> cellsToVisit; //indices of cell to visit in the next iteration of the algorithm
    std::set<int> visitedCells; //indices of cell marked as visited by algorithm
    cellsToVisit.insert(idxStart);
    distToCells[idxStart] = 0;
   
    bool stop = false;

    //find short path
    while (cellsToVisit.size() > 0) {
        std::set<int>::iterator iter_idx(cellsToVisit.begin());
        std::set<int> cellsForNextRound; //indices
        while (iter_idx != cellsToVisit.end()) {
            float thisCellDist = distToCells[*iter_idx]; //current distance until this cell
            int row = Direction::row(*iter_idx, cols);
            int col = Direction::col(*iter_idx, cols);
            // 8 surrounding cells
            for (int r = -1; r <= 1; ++r) {
                for (int c = -1; c <= 1; ++c) {
                    if (c != 0 || r != 0) {
                        int nextIdx = (row+r) * cols + (col+c);
                        if (visitedCells.find(nextIdx) == visitedCells.end() && cellsToVisit.find(nextIdx) == cellsToVisit.end()) {
                            std::map<int, float>::iterator nextCell = distToCells.find(nextIdx); 
                            if (nextCell != distToCells.end()) { //the cell is in distToCells thus is walkable
                                if (nextIdx != idxGoal) {
                                    cellsForNextRound.insert(nextIdx);
                                } else {
                                    stop = true; // stop the algorithms if the goal is achieved in the current iteration
                                }
                                float step = (c != 0 && r != 0) ? 1.414 : 1.0; // distance between two cells
                                float newDistance = thisCellDist + step;
                                if (nextCell->second > newDistance) {
                                    nextCell->second = newDistance;
                                    previousCells[nextIdx] = *iter_idx;
                                }
                            }
                        }
                    }
                }
            }
            ++iter_idx;
        }
        visitedCells.insert(cellsToVisit.begin(), cellsToVisit.end());
        if (stop) {
            break;
        }
        cellsToVisit = cellsForNextRound;
    }
    
    // find the path backwards
    int idxCell = idxGoal;
    int nextCell = idxCell;


    while (idxCell != idxStart) {
        nextCell = idxCell;
        std::map<int, int>::iterator idx_prev = previousCells.find(idxCell);
        if (idx_prev != previousCells.end()) {
            idxCell = idx_prev->second;
            int r = Direction::row(idxCell, cols);
            int c = Direction::col(idxCell, cols);
            this->world->debug->addMarkerAt(r, c);
        } else { //algorithm didnt reached the cell thus something went wrong
            std::cout << "Goal wasnt reached\n";
            return this->seal->direction; // goal wasnt reached
        }
    }
    
    int colNext = Direction::col(nextCell, cols);
    int rowNext = Direction::row(nextCell, cols);


    int x = colNext - colStart;
    int y = rowNext - rowStart;
    
    return Direction::direction(x, y);    
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
