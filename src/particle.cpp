#include "particle.h"
#include <QPainter>

Particle::Particle()
{
    spriteframe = qrand() % 8;
    spritesheet = QPixmap("../resources/seal-spritesheet.png");
}

QRectF Particle::boundingRect() const
{
    return QRectF(-16, -16, 32, 32);
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // TODO: look into using QGraphicsPixmapItem instead of QGraphicsItem
    painter->drawPixmap(-16, -16, spritesheet, spriteframe * 32, 0, 32, 32);
}

void Particle::advance(int step)
{
    Q_UNUSED(step);
    moveBy(-1.0 + qrand() % 3, -1.0 + qrand() % 3);
}
