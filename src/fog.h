#ifndef FOG_H
#define FOG_H

#include <vector>

class World;
class Fog
{
public:
    World *world;
    std::vector<int> *vertices;

    Fog(World *world);
    void clearTile(int row, int col);
    void advance();

private:
    int condensationTime = 160;
    int worldWidth;
    int worldHeight;
};

#endif // FOG_H
