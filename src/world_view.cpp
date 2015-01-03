#include "world_view.h"
#include "seal_view.h"

WorldView::WorldView(World *world)
{
    this->world = world;

    int rows = this->world->height;
    int cols = this->world->width;

    this->scene = new QGraphicsScene();
    // Scenes are infinite, but Qt can better optimize performance when the size is constrained.
    this->scene->setSceneRect(0, 0, cols * tileSize, rows * tileSize);
    // Disable indexing of item positions for better performance.
    this->scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    this->terrain = new TerrainView(rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            this->terrain->setTile(row, col, this->world->terrain->getTile(row, col));
        }
    }
    this->scene->addItem(this->terrain);

    for (std::size_t i = 0; i < this->world->seals->size(); i++) {
        this->scene->addItem(new SealView(this->world->seals->at(i)));
    }

    this->fog = new FogView(this->world->fog);
    this->scene->addItem(this->fog);

    this->grid = new GridOverlay(rows, cols);
    this->scene->addItem(this->grid);

    this->widget = new TimeableGraphicsView(this->scene);
    this->widget->setCacheMode(QGraphicsView::CacheBackground);
    this->widget->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->widget->setBackgroundBrush(Qt::black);
    this->widget->setFrameShape(QFrame::NoFrame);
}

void WorldView::scaleToFit()
{
    this->widget->setRenderHint(QPainter::SmoothPixmapTransform, true);
    this->widget->fitInView(this->scene->sceneRect(), Qt::KeepAspectRatio);
}

void WorldView::resetScale()
{
    this->widget->setRenderHint(QPainter::SmoothPixmapTransform, false);
    this->widget->resetTransform();
}


void WorldView::advance()
{
    this->scene->advance();
}

QString WorldView::getAveragePaintTimeAsString()
{
    return this->widget->stopwatch.getAverageTimeAsString();
}

void WorldView::toggleFog(bool visible)
{
    this->fog->setVisible(visible);
}

void WorldView::toggleGrid(bool visible)
{
    this->grid->setVisible(visible);
}