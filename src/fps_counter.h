#ifndef FPS_COUNTER
#define FPS_COUNTER

#include <QtGui>

class FPSCounter
{
public:
    FPSCounter();
    float tick();

private:
    QElapsedTimer *timer;
    float averageFPS;
};

#endif // FPS_COUNTER
