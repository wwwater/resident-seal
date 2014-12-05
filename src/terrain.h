#ifndef TERRAIN_H
#define TERRAIN_H

#include <QtWidgets>

class Terrain
{
public:
    int width = 0;
    int height = 0;

    void loadFromFile(QString filename);
    void loadObstaclesFromFile(QString filename);
    int getTile(int row, int column);
    bool isObstacle(int row, int column);

private:
    // Stored in row-major order.
    std::vector <int> tiles;

    // Indicates which tile types (not positions) are obstacles.
    std::vector <bool> obstacles;
};

#endif // TERRAIN_H
