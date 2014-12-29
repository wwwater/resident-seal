#ifndef TERRAIN_VIEW_H
#define TERRAIN_VIEW_H

#include <QGraphicsItem>

class TerrainView : public QGraphicsItem
{
public:
    const int tileSize = 32;
    bool showGrid = false;

    TerrainView(int rows, int cols);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTile(int row, int col, int tileIndex);

private:
    QPixmap terrainImage;
    QPixmap spritesheet;
};

#endif // TERRAIN_VIEW_H
