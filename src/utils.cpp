#include <QtGlobal>
#include "utils.h"
#include <map>
#include <set>

float Direction::x(int dir)
{
    switch (dir) {
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

float Direction::y(int dir)
{
    return x((dir + 6) % 8);
}

int Direction::intX(int dir)
{
    return qRound(x(dir));
}

int Direction::intY(int dir)
{
    return qRound(y(dir));
}

int Direction::rotate(int dir, int turns)
{
    dir = (dir + turns) % 8;
    return dir < 0 ? 8 + dir : dir;
}

int Direction::col(int idx, int cols)
{
    return idx % cols;
}

int Direction::row(int idx, int cols)
{
    return (idx - col(idx, cols)) / cols; 
}

int Direction::direction(int x, int y)
{
    if (x ==  0 && y == -1) return 0;
    if (x ==  1 && y == -1) return 1;
    if (x ==  1 && y ==  0) return 2;
    if (x ==  1 && y ==  1) return 3;
    if (x ==  0 && y ==  1) return 4;
    if (x == -1 && y ==  1) return 5;
    if (x == -1 && y ==  0) return 6;
    if (x == -1 && y == -1) return 7;
    return 0;
}

int randint(int min, int max)
{
    return min + qrand() % (max + 1 - min);
}

std::vector<std::pair<int, int>> Direction::pathToGoal(int rows, int cols, 
                               int rowStart, int colStart, int rowGoal, int colGoal,
                               std::function<bool (int, int)> hasObstacleAt) 
{
    //distances to the cells from the starting position
    std::map<int, float> distToCells;
    std::map<int, int> previousCells; //for extraction the path
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!hasObstacleAt(r, c)) {
                distToCells.insert(distToCells.end(), 
                                std::pair<int, float>(r * cols + c, rows + cols));
            }
        }
    }
    int idxStart = rowStart * cols + colStart;
    int idxGoal = rowGoal * cols + colGoal;

    //indices of cell to visit in the next iteration of the algorithm
    std::set<int> cellsToVisit; 
    //indices of cell marked as visited by algorithm
    std::set<int> visitedCells;
    cellsToVisit.insert(idxStart);
    distToCells[idxStart] = 0;
   
    bool stop = false;

    //find short path
    while (cellsToVisit.size() > 0) {
        std::set<int>::iterator iter_idx(cellsToVisit.begin());
        std::set<int> cellsForNextRound; //indices
        while (iter_idx != cellsToVisit.end()) {
             //current distance until this cell
            float thisCellDist = distToCells[*iter_idx];
            int row = Direction::row(*iter_idx, cols);
            int col = Direction::col(*iter_idx, cols);
            // 8 surrounding cells
            for (int r = -1; r <= 1; ++r) {
                for (int c = -1; c <= 1; ++c) {
                    if (c != 0 || r != 0) {
                        int nextIdx = (row+r) * cols + (col+c);
                        if (visitedCells.find(nextIdx) == visitedCells.end()
                         && cellsToVisit.find(nextIdx) == cellsToVisit.end()) {
                            std::map<int, float>::iterator nextCell = 
                                distToCells.find(nextIdx);
                            //the cell is in distToCells thus is walkable
                            if (nextCell != distToCells.end()) {
                                if (nextIdx != idxGoal) {
                                    cellsForNextRound.insert(nextIdx);
                                } else {
                                    // stop the algorithms in the current iteration
                                    stop = true;
                                }
                                // distance between two cells
                                float step = (c != 0 && r != 0) ? 1.414 : 1.0;
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
    std::vector<std::pair<int, int>> path;

    while (idxCell != idxStart) {
        int row = Direction::row(idxCell, cols);
        int col = Direction::col(idxCell, cols);
        path.push_back(std::make_pair(row, col));
        std::map<int, int>::iterator idx_prev = previousCells.find(idxCell);
        if (idx_prev != previousCells.end()) {
            idxCell = idx_prev->second;
        } else { //algorithm didnt reached the cell thus something went wrong
            std::vector<std::pair<int, int>> zero; // goal wasnt reached
            return zero;
        }
    }
    return path;
}

int Direction::turnDirection(int directionIs, int directionToBe)
{
    int diff = directionToBe - directionIs;
    if (diff == 0) return 0;
    else if (diff < -4 || (diff > 0 && diff < 4)) return 1;
    return -1;
}
