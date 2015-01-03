#include "fog.h"
#include "world.h"

Fog::Fog(World *world)
{
    this->world = world;
    this->worldWidth = world->width;
    this->worldHeight = world->height;
    this->vertices = new std::vector<int>;
    this->vertices->assign((world->width + 1) * (world->height + 1), 0);
}

void Fog::clearTile(int row, int col)
{    
    this->vertices->at((row + 0) * this->worldWidth + col + 0) = this->condensationTime;
    this->vertices->at((row + 0) * this->worldWidth + col + 1) = this->condensationTime;
    this->vertices->at((row + 1) * this->worldWidth + col + 0) = this->condensationTime;
    this->vertices->at((row + 1) * this->worldWidth + col + 1) = this->condensationTime;
}

void Fog::advance()
{

    int vertexCount = this->vertices->size();
    for (int i = 0; i < vertexCount; i++) {
        if (this->vertices->at(i) > 1) {
            this->vertices->at(i) -= 1;
        }
    }
}
