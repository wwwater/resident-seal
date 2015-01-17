#ifndef DEBUG_H
#define DEBUG_H

#include <vector>

class World;
class Debug
{
public:
    int rows;
    int cols;
    World *world;
    std::vector<int> *markers;

    Debug(World *world);
    void addMarkerAt(int row, int col);
    void clearMarkerAt(int row, int col);
};

#endif // DEBUG_H
