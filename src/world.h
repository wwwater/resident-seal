#ifndef WORLD_H
#define WORLD_H

#include "seal.h"
#include "fog.h"
#include "terrain.h"

class World
{
public:
    int width;
    int height;
    Terrain *terrain;
    Fog *fog;
    std::vector<Seal *> *seals;
    std::vector<Seal *> *seals_by_location;

    World(Terrain *terrain);
    void addSeal(Seal *seal);
    Seal* getSealAt(int row, int col);
    void putSealAt(Seal *seal, int row, int col);
    bool hasSealAt(int row, int col);
    bool hasObstacleAt(int row, int col);
    void advance();
};

#endif // WORLD_H
