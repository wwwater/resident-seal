#include "debug_view.h"
#include <QPainter>

DebugView::DebugView(Debug *model)
{
    this->model = model;
    this->rows = model->rows;
    this->cols = model->cols;
    this->markers = new std::vector<int>;
    this->markers->assign(rows * cols, 0);
}

QRectF DebugView::boundingRect() const
{
    return QRectF(0, 0, cols * tileSize, rows * tileSize);
}

void DebugView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(213, 0, 249, 128));

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            if (markers->at(row * cols + col)) {
                int x = col * tileSize + tileSize / 2;
                int y = row * tileSize + tileSize / 2;
                painter->drawEllipse(QPoint(x, y), 8, 8);
            }
        }
    }
}

void DebugView::advance(int phase)
{
    if (!phase) {
        return;
    }

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            int i = row * cols + col;
            if (markers->at(i) != model->markers->at(i)) {
                markers->at(i) = model->markers->at(i);
                update(col * tileSize, row * tileSize, tileSize, tileSize);
            }
        }
    }
}
