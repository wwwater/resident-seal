#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <vector>

class Cell
{
public:
    int row;
    int col;
    Cell(int row, int col);
    std::vector<Cell> neighbors();
    float distanceToNeighbor(Cell &that);
    friend bool operator <(Cell const &cell1, Cell const &cell2);
    friend bool operator ==(Cell const &cell1, Cell const &cell2);
    friend bool operator !=(Cell const &cell1, Cell const &cell2);
};

class MovingObject
{
public:
    float x;
    float y;
    int direction;
    int rows;
    int cols;
    MovingObject(float x, float y, int dir);
    int row();
    int col();
    Cell cell();
    float dx();
    float dy();
    void rotate(int turns);
    int rowAhead();
    int colAhead();
    Cell nextCell();
    int directionTo(Cell &cell);
    int turnDirectionTo(Cell &cell);
};


class Algorithms
{
public:
    static std::vector<Cell> pathToGoal(int rows, int cols,
                               Cell start, Cell goal,
                               std::function<bool (int, int)> hasObstacleAt);

};

int randint(int min, int max);
#endif // UTILS_H
