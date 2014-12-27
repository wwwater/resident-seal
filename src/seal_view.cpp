#include "seal_view.h"
#include <QPainter>

QPixmap *SealView::getPixmap()
{
    static QPixmap *sprite = new QPixmap("../resources/seal-spritesheet.png");
    return sprite;
}

SealView::SealView(Seal *seal)
{
    this->seal = seal;
}

QRectF SealView::boundingRect() const
{
    return QRectF(-tileSize/2, -tileSize/2, tileSize, tileSize);
}

void SealView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-tileSize/2, -tileSize/2, *SealView::getPixmap(),
                        direction * tileSize, 0, tileSize, tileSize);
}

void SealView::advance(int step)
{
    Q_UNUSED(step);
    setDirection(this->seal->direction);
    setPos(this->seal->x * tileSize, this->seal->y * tileSize);
}

void SealView::setDirection(int newDirection)
{
    direction = newDirection % 8;
}
