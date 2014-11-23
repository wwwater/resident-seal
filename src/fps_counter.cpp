#include "fps_counter.h"

FPSCounter::FPSCounter()
{
    timer = new QElapsedTimer();
    averageFPS = 0;
}

float FPSCounter::tick()
{
    // Exponential moving average
    return averageFPS += 0.05 * (1000.0 / timer->restart() - averageFPS);
}