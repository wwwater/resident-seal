#include "seal.h"
#include <cmath>

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
    return ((fabs(x - floor(x) - 0.5) < 0.05) && (fabs(y - floor(y) - 0.5) < 0.05));
}

void Seal::advance()
{
    if (this->tiredness >= this->maxTiredness && isAtCellCentre(this->x, this->y)) {

        this->isMoving = false;
    }
    
    if (!this->isMoving) {
        /* // let the seal look aroung while resting. doesnt work!
        if (qrand() % 10 == 0) {
            this->direction = qrand() % 8;
        }*/

        this->tiredness -= this->rateRecovery;
        if (this->tiredness <= minTiredness) {
            this->isMoving = bool(qrand() % 2);
            this->direction = qrand() % 8;
        }
    } else {
        float step = this->stepSize;
        if (direction % 2 == 1) {
            step /= 1.4142136;
        }

        // Which one do you like more? This:
        if (direction > 0 && direction < 4) {
            this->x +=step;
        }

        if (direction > 4 && direction < 8) {
            this->x -=step;
        }

        if (direction > 2 && direction < 6) {
            this->y +=step;
        }

        if (direction == 0 || direction == 1 || direction == 7) {
            this->y -=step;
        }

        /* Or this:
        switch(direction) {
            case(0):
                this->x += 0;
                this->y += -step;
                break;
            case(1):
                this->x += step;
                this->y += -step;
                break;
            case(2):
                this->x += step;
                this->y += 0;
                break;
            case(3):
                this->x += step;
                this->y += step;
                break;
            case(4):
                this->x += 0;
                this->y += step;
                break;
            case(5):
                this->x += -step;
                this->y += step;
                break;
            case(6):
                this->x += -step;
                this->y += 0;
                break;
            case(7):
                this->x += -step;
                this->y += -step;
        }*/

        this->tiredness += rateTiredness;
    }
}

