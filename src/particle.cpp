#include "particle.h"
#include <QPainter>

QPixmap *Particle::getPixmap()
{
    static QPixmap *sprite = new QPixmap("../resources/seal-spritesheet.png");
    return sprite;
}

Particle::Particle()
{
    spriteframe = qrand() % 8;
}

QRectF Particle::boundingRect() const
{
    return QRectF(-16, -16, 32, 32);
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // TODO: look into using QGraphicsPixmapItem instead of QGraphicsItem
    painter->drawPixmap(-16, -16, *Particle::getPixmap(), spriteframe * 32, 0, 32, 32);
}

void Particle::advance(int step)
{
    Q_UNUSED(step);
    moveBy(-1.0 + qrand() % 3, -1.0 + qrand() % 3);
}
