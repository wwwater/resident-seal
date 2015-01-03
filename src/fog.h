#ifndef FOG_H
#define FOG_H

#include <vector>

class World;
class Fog
{
public:
    World *world;
    int worldWidth;
    int worldHeight;
    std::vector<int> *vertices;

    Fog(World *world);
    void clearTile(int row, int col);
    void advance();

private:
    int condensationTime = 160;
};

#endif // FOG_H
