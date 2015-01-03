#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include <QGraphicsView>
#include "world.h"
#include "performance_timer.h"
#include "terrain_view.h"
#include "fog_view.h"

class TimeableGraphicsView : public QGraphicsView
{
    using QGraphicsView::QGraphicsView;
public:
    PerformanceTimer stopwatch;
protected:
    void paintEvent(QPaintEvent *event)
    {
        this->stopwatch.reset();
        QGraphicsView::paintEvent(event);
        this->stopwatch.lap();
    }
};

class WorldView
{
public:
    const int tileSize = 32;
    World *world;
    TimeableGraphicsView *widget;

    WorldView(World *world);
    void advance();
    void scaleToFit();
    void resetScale();
    QString getAveragePaintTimeAsString();

private:
    QGraphicsScene *scene;
    TerrainView *terrain;
    FogView *fog;
};

#endif // WORLD_VIEW_H
