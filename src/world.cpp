#include "world.h"

World::World(Terrain *terrain)
{
    this->terrain = terrain;
    this->width = terrain->width;
    this->height = terrain->height;
    this->seals = new std::vector<Seal *>;
    this->seals_by_location = new std::vector<Seal *>;
    this->seals_by_location->assign(this->width * this->height, NULL);
}

void World::addSeal(Seal *seal)
{
    seal->world = this;
    this->seals->push_back(seal);
    this->putSealAt(seal, floor(seal->y), floor(seal->x));
}

void World::advance()
{
    for (std::size_t i = 0; i < this->seals->size(); i++) {
        this->seals->at(i)->advance();
    }
}

Seal* World::getSealAt(int row, int col)
{
    return this->seals_by_location->at(row * this->width + col);
}

void World::putSealAt(Seal *seal, int row, int col)
{
    this->seals_by_location->at(row * this->width + col) = seal;
}

bool World::hasSealAt(int row, int col)
{
    return this->getSealAt(row, col) != NULL;
}

bool World::hasObstacleAt(int row, int col)
{
    return this->terrain->isObstacle(row, col);
}
