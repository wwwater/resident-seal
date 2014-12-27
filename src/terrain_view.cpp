#include "terrain_view.h"
#include <QPainter>

TerrainView::TerrainView(int rows, int cols)
{
    spritesheet = QPixmap("../resources/terrain-spritesheet.png");
    terrainImage = QPixmap(cols * tileSize, rows * tileSize);
}

QRectF TerrainView::boundingRect() const
{
    return QRectF(0, 0, terrainImage.width(), terrainImage.height());
}

void TerrainView::setTile(int row, int col, int tileIndex)
{
    int totalTiles = spritesheet.width() / tileSize;
    QPainter painter(&terrainImage);
    painter.drawPixmap(col * tileSize, row * tileSize, tileSize, tileSize,
        spritesheet, (tileIndex % totalTiles) * tileSize, 0, tileSize, tileSize);

    // Show grid for debugging purpose
    painter.setPen(QColor(0, 0, 0, 20));
    painter.drawRect(col * tileSize, row * tileSize, tileSize, tileSize);
}

void TerrainView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, terrainImage, 0, 0, terrainImage.width(), terrainImage.height());
}
