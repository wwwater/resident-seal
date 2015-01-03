#include "fog_view.h"
#include <QPainter>

FogView::FogView(Fog *fog)
{
    this->fog = fog;
    this->fogImage = QPixmap(fog->worldWidth * tileSize, fog->worldHeight * tileSize);
    this->spritesheet = QPixmap("../resources/fog-spritesheet.png");

    // Remember what each tile looks like to avoid redrawing it if it didn't change.
    this->fingerprints = new std::vector<int>;
    this->fingerprints->assign(fog->worldWidth * fog->worldHeight, -1);
}

QRectF FogView::boundingRect() const
{
    return QRectF(0, 0, fogImage.width(), fogImage.height());
}

void FogView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setCompositionMode(QPainter::CompositionMode_Multiply);
    painter->drawPixmap(0, 0, fogImage, 0, 0, fogImage.width(), fogImage.height());
}

void FogView::advance(int step)
{
    Q_UNUSED(step);

    QPainter painter(&fogImage);
    int rows = this->fog->worldHeight;
    int cols = this->fog->worldWidth;
    std::vector<int> *fog_vertices = this->fog->vertices;

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            // Tile corners: top-left, top-right, bottom-left, bottom-right
            int a = fog_vertices->at((row + 0) * cols + col + 0);
            int b = fog_vertices->at((row + 0) * cols + col + 1);
            int c = fog_vertices->at((row + 1) * cols + col + 0);
            int d = fog_vertices->at((row + 1) * cols + col + 1);

            // Positions of black and white part of the fog in spritesheet
            int black = (a < 1 ? 1:0) + (b < 1 ? 2:0) + (c < 1 ? 4:0) + (d < 1 ? 8:0);
            int white = (a > 1 ? 1:0) + (b > 1 ? 2:0) + (c > 1 ? 4:0) + (d > 1 ? 8:0);

            int fingerprint = white * 16 + black;
            if (this->fingerprints->at(row * cols + col) == fingerprint) {
                continue;
            }
            this->fingerprints->at(row * cols + col) = fingerprint;


            painter.eraseRect(col * tileSize, row * tileSize, tileSize, tileSize);

            if (black > 0) {
                painter.drawPixmap(col * tileSize, row * tileSize, this->spritesheet,
                    black * tileSize, 0, tileSize, tileSize);
            }

            if (white < 15) {
                painter.drawPixmap(col * tileSize, row * tileSize, this->spritesheet,
                    white * tileSize, tileSize, tileSize, tileSize);
            }
        }
    }
}