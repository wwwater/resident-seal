#include "terrain.h"

void Terrain::loadFromFile(const QString &filename)
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

int Terrain::getTile(int row, int column)
{
    return this->tiles[row * this->width + column];
}
