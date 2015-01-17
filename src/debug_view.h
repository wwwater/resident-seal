#ifndef DEBUG_VIEW_H
#define DEBUG_VIEW_H

#include <QGraphicsItem>
#include <vector>
#include "debug.h"

class DebugView : public QGraphicsItem
{
public:
    const int tileSize = 32;
    int rows;
    int cols;
    std::vector<int> *markers;
    Debug *model;

    DebugView(Debug *model);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void advance(int step);
};

#endif // DEBUG_VIEW_H
