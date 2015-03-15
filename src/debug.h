#ifndef DEBUG_H
#define DEBUG_H

#include <vector>
#include "utils.h"

class World;
class Debug
{
public:
    int rows;
    int cols;
    World *world;
    std::vector<int> *markers;

    Debug(World *world);
    void addMarkerAt(Cell cell);
    void clearMarkerAt(Cell cell);
};

#endif // DEBUG_H
