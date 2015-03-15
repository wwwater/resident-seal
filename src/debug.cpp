#include "debug.h"
#include "world.h"

Debug::Debug(World *world)
{
    this->rows = world->height;
    this->cols = world->width;
    this->markers = new std::vector<int>;
    this->markers->assign(rows * cols, 0);
}

void Debug::addMarkerAt(Cell cell)
{
    this->markers->at(cell.row * this->cols + cell.col) = 1;
}

void Debug::clearMarkerAt(Cell cell)
{
    this->markers->at(cell.row * this->cols + cell.col) = 0;
}
