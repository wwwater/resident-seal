#include <functional>
#include <vector>
class Direction
{
public:
    static float x(int dir);
    static float y(int dir);
    static int intX(int dir);
    static int intY(int dir);
    static int rotate(int dir, int turns);
    static int col(int idx, int cols);
    static int row(int idx, int cols);
    static int direction(int x, int y);
    static std::vector<int> pathToGoal(int rows, int cols,
                               int rowStart, int colStart, 
                               int rowGoal, int colGoal,
                               std::function<bool (int, int)> hasObstacleAt);
};

int randint(int min, int max);
