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
    this->putSealAt(seal, seal->cell());
}

void World::advance()
{
    this->fog->advance();
    for (std::size_t i = 0; i < this->seals->size(); i++) {
        this->seals->at(i)->advance();
    }
}

Seal* World::getSealAt(Cell cell)
{
    return this->sealsByLocation->at(cell.row * this->width + cell.col);
}

void World::putSealAt(Seal *seal, Cell cell)
{
    this->sealsByLocation->at(cell.row * this->width + cell.col) = seal;

    if (seal == NULL) {
        this->debug->clearMarkerAt(cell);
    } else {
        this->debug->addMarkerAt(cell);
    }
}

bool World::hasSealAt(Cell cell)
{
    return this->getSealAt(cell) != NULL;
}

bool World::hasObstacleAt(Cell cell)
{
    return this->terrain->isObstacle(cell);
}
