#ifndef FOG_H
#define FOG_H

#include <vector>
#include "utils.h"

class World;
class Fog
{
public:
    World *world;
    int worldWidth;
    int worldHeight;
    std::vector<int> *vertices;

    Fog(World *world);
    void clearTile(Cell cell);
    void advance();

private:
    int condensationTime = 160;
};

#endif // FOG_H
