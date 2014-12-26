#ifndef WORLD_H
#define WORLD_H

#include "seal.h"
#include "terrain.h"

class World
{
public:
    Terrain *terrain;
    std::vector<Seal *> seals;

    World(Terrain *terrain);
    void addSeal(Seal *seal);
    void advance();
};

#endif // WORLD_H
