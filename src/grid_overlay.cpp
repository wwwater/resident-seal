#include "grid_overlay.h"
#include <QPainter>

QRectF GridOverlay::boundingRect() const
{
    return QRectF(0, 0, cols * tileSize, rows * tileSize);
}

void GridOverlay::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QColor(90, 90, 90, 64));
    for (int row = 0; row < rows; row++) {
        painter->drawLine(0, row * tileSize, cols * tileSize, row * tileSize);
    }
    for (int col = 0; col < cols; col++) {
        painter->drawLine(col * tileSize, 0, col * tileSize, rows * tileSize);
    }
}
