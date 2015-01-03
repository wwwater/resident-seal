#ifndef WORLD_VIEW_H
#define WORLD_VIEW_H

#include <QGraphicsView>
#include "world.h"
#include "performance_timer.h"
#include "terrain_view.h"
#include "fog_view.h"
#include "grid_overlay.h"

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
    QString getAveragePaintTimeAsString();
    void toggleFog(bool visible);
    void toggleGrid(bool visible);
    void scaleToFit();
    void resetScale();

private:
    QGraphicsScene *scene;
    TerrainView *terrain;
    FogView *fog;
    GridOverlay *grid;
};

#endif // WORLD_VIEW_H
