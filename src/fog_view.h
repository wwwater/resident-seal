#ifndef FOG_VIEW_H
#define FOG_VIEW_H

#include <QGraphicsItem>
#include "fog.h"

class FogView : public QGraphicsItem
{
public:
    Fog *fog;
    QPixmap *sprite;

    FogView(Fog *fog);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


class FogTile : public QGraphicsItem
{
public:
    const int tileSize = 32;
    int row, col, black = -1, white = -1;
    Fog *fog;
    QPixmap *sprite;

    FogTile(FogView *parent, int row, int col);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int step);
};

#endif // FOG_VIEW_H
