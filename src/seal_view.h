#ifndef SEAL_VIEW_H
#define SEAL_VIEW_H

#include <QGraphicsItem>
#include "seal.h"

class SealView : public QGraphicsItem
{
public:
    const int tileSize = 32;

    SealView(Seal* seal);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setDirection(int newDirection);

protected:
    void advance(int step);

private:
    Seal *seal;
    static QPixmap *getPixmap();
    int direction = 0;
};

#endif // SEAL_VIEW_H
