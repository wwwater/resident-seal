#include "world.h"

void World::World(Terrain *terrain)
{
    this.terrain = terrain;
}

void World::addSeal(Seal *seal)
{
    this.seals.push_back(seal);
}

void World::advance()
{
    for (int i = 0; i < this.seals.size(); i++) {
        this.seals[i]->advance();
    }
}
