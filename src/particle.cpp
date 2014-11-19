#include "particle.h"
#include <QPainter>

QRectF Particle::boundingRect() const
{
    return QRectF(-20, -20, 40, 40);
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(255, 255, 255, 200));
    painter->drawEllipse(-20, -20, 40, 40);
}

void Particle::advance(int step)
{
    Q_UNUSED(step);
    moveBy(-1.0 + qrand() % 3, -1.0 + qrand() % 3);
}
