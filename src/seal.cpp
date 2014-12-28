#include "seal.h"
#include "world.h"

Seal::Seal(int row, int col, int direction)
{
    this->x = col + 0.5;
    this->y = row + 0.5;
    this->direction = direction;
    this->isMoving = false;
    this->tiredness = 0;
    this->maxTiredness = 550 + (qrand() % 101);
    this->minTiredness = 0 + (qrand() % 101);
    this->rateTiredness = 1 + (qrand() % 5);
    this->rateRecovery = 1 + (qrand() % 5);
}

bool isAtCellCentre(float x, float y) 
{
    return std::abs(x - floor(x) - 0.5) < 0.05 &&
           std::abs(y - floor(y) - 0.5) < 0.05;
}

void Seal::advance()
{
    if (this->tiredness >= this->maxTiredness && isAtCellCentre(this->x, this->y)) {
        this->isMoving = false;
    }
    
    if (!this->isMoving) {
        this->tiredness -= this->rateRecovery;
        if (this->tiredness <= minTiredness) {
            this->isMoving = bool(qrand() % 2);
            this->direction = qrand() % 8;
        }
    } else {
        float dx = 0;
        float dy = 0;
        float step = this->stepSize;

        if (direction % 2 == 1) {
            step /= 1.4142136;
        }

        if (direction > 0 && direction < 4) {
            dx = step;
        }

        if (direction > 4 && direction < 8) {
            dx = -step;
        }

        if (direction > 2 && direction < 6) {
            dy = step;
        }

        if (direction == 0 || direction == 1 || direction == 7) {
            dy = -step;
        }

        // Are we about to cross into another cell?
        int oldRow    = floor(this->y);
        int oldCol    = floor(this->x);
        int newRow    = floor(this->y + dy);
        int newCol    = floor(this->x + dx);
        bool crossing = (newRow != oldRow || newCol != oldCol);

        if (crossing && this->world->hasSealAt(newRow, newCol)) {
            // Occupied by another seal, retreat!
            this->direction = (direction + 4) % 8;
            dx *= -1;
            dy *= -1;
        } else if (crossing) {
            this->world->putSealAt(NULL, oldRow, oldCol);
            this->world->putSealAt(this, newRow, newCol);
        }

        this->x += dx;
        this->y += dy;
        this->tiredness += rateTiredness;
    }
}
