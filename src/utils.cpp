#include <QtGlobal>
#include "utils.h"
#include <map>
#include <set>

Cell::Cell(int row, int col) : row(row), col(col)
{
}

std::vector<Cell> Cell::neighbors()
{
    std::vector<Cell> ns;
    for (int r = -1; r <= 1; ++r) {
        for (int c = -1; c <= 1; ++c) {
            if (c != 0 || r != 0) {
                ns.push_back(Cell(this->row + r, this->col + c));
            }
        }
    }
    return ns;
}

float Cell::distanceToNeighbor(Cell &that)
{
    int dy = that.row - this->row;
    int dx = that.col - this->col;
    if (dx == 0 || dy == 0) {
        return 1.0;
    } else {
        return 1.414;     
    }
}

bool operator <(Cell const &cell1, Cell const &cell2)
{
    if (cell1.row < cell2.row) return true;
    else if (cell1.row > cell2.row) return false;
    else if (cell1.col < cell2.col) return true;
    return false;
}

bool operator ==(Cell const &cell1, Cell const &cell2)
{
    return (cell1.row == cell2.row && cell1.col == cell2.col);
}

bool operator !=(Cell const &cell1, Cell const &cell2)
{
    return !(cell1 == cell2);
}

MovingObject::MovingObject(float x, float y, int dir) :
    x(x), y(y), direction(dir) 
{
}

int MovingObject::row()
{
    return int(this->y);
}

int MovingObject::col()
{
    return int(this->x);
}

float MovingObject::dx()
{
    switch (this->direction) {
        case 1:
        case 3:
            return 0.7071067811865476;
        case 5:
        case 7:
            return -0.7071067811865476;
        case 2:
            return 1;
        case 6:
            return -1;
        default:
            return 0;
    }
}

float MovingObject::dy()
{
    switch ((this->direction + 6) % 8) {
        case 1:
        case 3:
            return 0.7071067811865476;
        case 5:
        case 7:
            return -0.7071067811865476;
        case 2:
            return 1;
        case 6:
            return -1;
        default:
            return 0;
    }
}

void MovingObject::rotate(int turns)
{
    int new_dir = (this->direction + turns) % 8;
    this->direction =  new_dir < 0 ? 8 + new_dir : new_dir;
}

int MovingObject::rowAhead()
{
    switch (this->direction) {
        case 0:
        case 1:
        case 7:
            return this->row() - 1;
        case 2:
        case 6:
            return this->row();
        case 3:
        case 4:
        case 5:
            return this->row() + 1;
        default:
            return this->row();
    }
}

int MovingObject::colAhead()
{
    switch (this->direction) {
        case 5:
        case 6:
        case 7:
            return this->col() - 1;
        case 0:
        case 4:
            return this->col();
        case 1:
        case 2:
        case 3:
            return this->col() + 1;
        default:
            return this->col();
    }
}

Cell MovingObject::nextCell()
{
    return Cell(this->rowAhead(), this->colAhead());
}

int MovingObject::directionTo(Cell &cell) // neighbouring cell
{
    int dx = cell.col - this->col();
    int dy = cell.row - this->row();
    if (dx ==  0 && dy == -1) return 0;
    if (dx ==  1 && dy == -1) return 1;
    if (dx ==  1 && dy ==  0) return 2;
    if (dx ==  1 && dy ==  1) return 3;
    if (dx ==  0 && dy ==  1) return 4;
    if (dx == -1 && dy ==  1) return 5;
    if (dx == -1 && dy ==  0) return 6;
    if (dx == -1 && dy == -1) return 7;
    return 0;
}

int MovingObject::turnDirectionTo(Cell &cell) // left / right / none
{
    int directionToBe = this->directionTo(cell);
    int diff = directionToBe - this->direction;
    if (diff == 0) return 0;
    else if (diff < -4 || (diff > 0 && diff < 4)) return 1;
    return -1;
}

Cell MovingObject::cell()
{
    return Cell(this->row(), this->col());
}

std::vector<Cell> Algorithms::pathToGoal(int rows, int cols, 
                               Cell start, Cell goal,
                               std::function<bool (int, int)> hasObstacleAt) 
{
    //distances to the cells from the starting position
    std::map<Cell, float> distToCells;
    std::map<Cell, Cell> previousCells; //for extraction the path
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!hasObstacleAt(r, c)) {
                distToCells.insert(distToCells.end(),
                                std::pair<Cell, float>(Cell(r, c), rows + cols));
            }
        }
    }

    //indices of cell to visit in the next iteration of the algorithm
    std::set<Cell> cellsToVisit; 
    //indices of cell marked as visited by algorithm
    std::set<Cell> visitedCells;
    cellsToVisit.insert(start);
    distToCells[start] = 0;
   
    bool stop = false;

    //find short path
    while (cellsToVisit.size() > 0) {
        std::set<Cell> cellsForNextRound; //indices
        for (Cell currentCell: cellsToVisit) {
             //current distance until this cell
            float thisCellDist = distToCells[currentCell];
            for (Cell neighbor: currentCell.neighbors()) {
                if (visitedCells.find(neighbor) == visitedCells.end()
                 && cellsToVisit.find(neighbor) == cellsToVisit.end()) {
                    std::map<Cell, float>::iterator neighborDist = 
                                distToCells.find(neighbor);
                            //the cell is in distToCells thus is walkable
                    if (neighborDist != distToCells.end()) {
                        if (neighbor != goal) {
                            cellsForNextRound.insert(neighbor);
                        } else {
                            // stop the algorithms in the current iteration
                            stop = true;
                        }
                        // distance between two cells
                        float step = currentCell.distanceToNeighbor(neighbor);
                        float newDistance = thisCellDist + step;
                        if (neighborDist->second > newDistance) {
                            neighborDist->second = newDistance;
                            auto iter_neighbor = previousCells.find(neighbor);
                            if (iter_neighbor != previousCells.end()) {
                                iter_neighbor->second = currentCell;
                            } else {
                                previousCells.insert(
                                        std::make_pair(neighbor, currentCell));
                            }
                        }
                    }
                }
            }
        }
        visitedCells.insert(cellsToVisit.begin(), cellsToVisit.end());
        if (stop) {
            break;
        }
        cellsToVisit = cellsForNextRound;
    }
    
    // find the path backwards
    Cell current = goal;
    std::vector<Cell> path;

    while (current != start) {
        path.push_back(current);
        std::map<Cell, Cell>::iterator iter_prev = previousCells.find(current);
        if (iter_prev != previousCells.end()) {
            current = iter_prev->second;
        } else { //algorithm didnt reach the cell thus something went wrong
            std::vector<Cell> zero; // goal wasnt reached
            return zero;
        }
    }
    return path;
}

int randint(int min, int max)
{
    return min + qrand() % (max + 1 - min);
}

