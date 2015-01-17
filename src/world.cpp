#include "world.h"

World::World(Terrain *terrain)
{
    this->terrain = terrain;
    this->width = terrain->width;
    this->height = terrain->height;
    this->fog = new Fog(this);
    this->debug = new Debug(this);
    this->seals = new std::vector<Seal *>;
    this->sealsByLocation = new std::vector<Seal *>;
    this->sealsByLocation->assign(this->width * this->height, NULL);
}

void World::addSeal(Seal *seal)
{
    this->seals->push_back(seal);
    this->putSealAt(seal, floor(seal->y), floor(seal->x));
}

void World::advance()
{
    this->fog->advance();
    for (std::size_t i = 0; i < this->seals->size(); i++) {
        this->seals->at(i)->advance();
    }
}

Seal* World::getSealAt(int row, int col)
{
    return this->sealsByLocation->at(row * this->width + col);
}

void World::putSealAt(Seal *seal, int row, int col)
{
    this->sealsByLocation->at(row * this->width + col) = seal;

    if (seal == NULL) {
        this->debug->clearMarkerAt(row, col);
    } else {
        this->debug->addMarkerAt(row, col);
    }
}

bool World::hasSealAt(int row, int col)
{
    return this->getSealAt(row, col) != NULL;
}

bool World::hasObstacleAt(int row, int col)
{
    return this->terrain->isObstacle(row, col);
}
