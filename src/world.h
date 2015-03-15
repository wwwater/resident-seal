#ifndef WORLD_H
#define WORLD_H

#include "seal.h"
#include "fog.h"
#include "terrain.h"
#include "debug.h"

class World
{
public:
    int width;
    int height;
    Terrain *terrain;
    Fog *fog;
    Debug *debug;
    std::vector<Seal *> *seals;
    std::vector<Seal *> *sealsByLocation;

    World(Terrain *terrain);
    void addSeal(Seal *seal);
    Seal* getSealAt(Cell cell);
    void putSealAt(Seal *seal, Cell cell);
    bool hasSealAt(Cell cell);
    bool hasObstacleAt(Cell cell);
    void advance();
};

#endif // WORLD_H
