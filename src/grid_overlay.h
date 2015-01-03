#ifndef GRID_OVERLAY_VIEW_H
#define GRID_OVERLAY_VIEW_H

#include <QGraphicsItem>

class GridOverlay : public QGraphicsItem
{
public:
    const int tileSize = 32;
    int rows;
    int cols;

    GridOverlay(int rows, int cols) : rows(rows), cols(cols) {};
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // GRID_OVERLAY_VIEW_H
