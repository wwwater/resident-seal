#include "terrain.h"

void Terrain::loadFromFile(QString filename)
{
    QFile file;
    QString fileContents;

    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    fileContents = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileContents.toUtf8());
    QJsonObject mapData = doc.object();
    this->width = mapData.value("width").toInt();
    this->height = mapData.value("height").toInt();
    QJsonArray tiles = mapData.value("tiles").toArray();
    for (int i = 0; i < tiles.size(); i++) {
        this->tiles.push_back(tiles[i].toInt());
    }
}

void Terrain::loadObstaclesFromFile(QString filename)
{
    QFile file;
    QString fileContents;

    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    fileContents = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileContents.toUtf8());
    QJsonArray obstacles = doc.array();
    for (int i = 0; i < obstacles.size(); i++) {
        this->obstacles.push_back(obstacles[i].toInt() > 0);
    }
}

int Terrain::getTile(int row, int col)
{
    return this->tiles[row * this->width + col];
}

bool Terrain::isObstacle(Cell cell)
{
    return this->obstacles[this->getTile(cell.row, cell.col)];
}
