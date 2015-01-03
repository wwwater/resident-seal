#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include <QGraphicsView>
#include "performance_timer.h"

class WorldView : public QGraphicsView
{
public:
    PerformanceTimer stopwatch;

    WorldView(QGraphicsScene *scene, QWidget* parent=0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // WORLD_VIEW_H
