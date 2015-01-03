#ifndef FOG_VIEW_H
#define FOG_VIEW_H

#include <QGraphicsItem>
#include "fog.h"

class FogView : public QGraphicsItem
{
public:
    const int tileSize = 32;

    FogView(Fog *fog);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int step);

private:
    Fog *fog;
    std::vector<int> *fingerprints;
    QPixmap fogImage;
    QPixmap spritesheet;
};

#endif // FOG_VIEW_H
