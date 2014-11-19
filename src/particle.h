#ifndef PARTICLE_H
#define PARTICLE_H

#include <QGraphicsItem>

class Particle : public QGraphicsItem
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);
};

#endif // PARTICLE_H
