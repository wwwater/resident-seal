#include "fog_view.h"
#include <QPainter>

FogView::FogView(Fog *fog)
{
    this->fog = fog;
    this->sprite = new QPixmap("../resources/fog-spritesheet.png");

    for (int row = 0; row < fog->worldHeight; row++) {
        for (int col = 0; col < fog->worldWidth; col++) {
            new FogTile(this, row, col);
        }
    }
}

QRectF FogView::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void FogView::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}

FogTile::FogTile(FogView *parent, int row, int col)
{
    this->fog = parent->fog;
    this->sprite = parent->sprite;
    this->row = row;
    this->col = col;

    this->setParentItem(parent);
    this->setPos(col * tileSize, row * tileSize);
}

QRectF FogTile::boundingRect() const
{
    return QRectF(0, 0, tileSize, tileSize);
}

void FogTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (black > 0) {
        painter->drawPixmap(0, 0, *sprite, black * tileSize, 0, tileSize, tileSize);
    }

    if (white < 15 && black < 15) {
        painter->drawPixmap(0, 0, *sprite, white * tileSize, tileSize, tileSize, tileSize);
    }
}

void FogTile::advance(int)
{
    std::vector<int> *fog = this->fog->vertices;
    int cols = this->fog->worldWidth;

    // Tile corners: top-left, top-right, bottom-left, bottom-right
    int a = fog->at((row + 0) * cols + col + 0);
    int b = fog->at((row + 0) * cols + col + 1);
    int c = fog->at((row + 1) * cols + col + 0);
    int d = fog->at((row + 1) * cols + col + 1);

    // Positions of black and white part of the fog in spritesheet
    int black = (a < 1 ? 1:0) + (b < 1 ? 2:0) + (c < 1 ? 4:0) + (d < 1 ? 8:0);
    int white = (a > 1 ? 1:0) + (b > 1 ? 2:0) + (c > 1 ? 4:0) + (d > 1 ? 8:0);

    if (black != this->black || white != this->white) {
        this->black = black;
        this->white = white;
        update();
    }
}