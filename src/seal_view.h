#ifndef SEAL_VIEW_H
#define SEAL_VIEW_H

#include <QGraphicsItem>

class SealView : public QGraphicsItem
{
public:
    const int tileSize = 32;

    SealView();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setDirection(int newDirection);

protected:
    void advance(int step);

private:
    static QPixmap *getPixmap();
    int direction = 0;
};

#endif // SEAL_VIEW_H
