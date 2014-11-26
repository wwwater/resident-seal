#include "seal_view.h"
#include <QPainter>

QPixmap *SealView::getPixmap()
{
    static QPixmap *sprite = new QPixmap("../resources/seal-spritesheet.png");
    return sprite;
}

SealView::SealView()
{

}

QRectF SealView::boundingRect() const
{
    return QRectF(-16, -16, 32, 32);
}

void SealView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // TODO: look into using QGraphicsPixmapItem instead of QGraphicsItem
    painter->drawPixmap(-16, -16, *SealView::getPixmap(), direction * 32, 0, 32, 32);
}

void SealView::advance(int step)
{
    Q_UNUSED(step);
    moveBy(-1.0 + qrand() % 3, -1.0 + qrand() % 3);
}

void SealView::setDirection(int newDirection)
{
    direction = newDirection % 8;
}