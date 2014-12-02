#ifndef TERRAIN_H
#define TERRAIN_H

#include <QtWidgets>

class Terrain
{
public:
    int width = 0;
    int height = 0;
    int getTile(int row, int column);
    void loadFromFile(const QString &filename);

private:
    // Stored in row-major order.
    std::vector <int> tiles;
};

#endif // TERRAIN_H
