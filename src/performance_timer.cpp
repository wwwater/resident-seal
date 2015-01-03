#include "performance_timer.h"

PerformanceTimer::PerformanceTimer()
{
    timer = new QElapsedTimer();
    averageTime = 0;
}

void PerformanceTimer::start()
{
    timer->start();
}

void PerformanceTimer::reset()
{
    timer->restart();
}

void PerformanceTimer::lap()
{
    // Exponential moving average
    averageTime += 0.05 * (timer->restart() - averageTime);
}

QString PerformanceTimer::getAverageTimeAsString()
{
    return QString::number(averageTime, 'f', 1) + "ms";
}

QString PerformanceTimer::getAverageFrequencyAsString()
{
    return QString::number(1000.0 / averageTime, 'f', 0);
}