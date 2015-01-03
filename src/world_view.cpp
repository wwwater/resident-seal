#include "world_view.h"

WorldView::WorldView(QGraphicsScene *scene, QWidget* parent)
: QGraphicsView(scene, parent)
{
    this->stopwatch = PerformanceTimer();
}

void WorldView::paintEvent(QPaintEvent *event)
{
    this->stopwatch.reset();
    QGraphicsView::paintEvent(event);
    this->stopwatch.lap();
}