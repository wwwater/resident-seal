#include "debug.h"
#include "world.h"

Debug::Debug(World *world)
{
    this->rows = world->height;
    this->cols = world->width;
    this->markers = new std::vector<int>;
    this->markers->assign(rows * cols, 0);
}

void Debug::addMarkerAt(int row, int col)
{
    this->markers->at(row * this->cols + col) = 1;
}

void Debug::clearMarkerAt(int row, int col)
{
    this->markers->at(row * this->cols + col) = 0;
}
