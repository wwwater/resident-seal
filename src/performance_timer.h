#ifndef PERFORMANCE_TIMER
#define PERFORMANCE_TIMER

#include <QtWidgets>

class PerformanceTimer
{
public:
    PerformanceTimer();
    void start();
    void reset();
    void lap();
    QString getAverageTimeAsString();
    QString getAverageFrequencyAsString();

private:
    QElapsedTimer *timer;
    float averageTime;
};

#endif // PERFORMANCE_TIMER
