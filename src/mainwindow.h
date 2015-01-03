#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "performance_timer.h"
#include "world.h"
#include "world_view.h"

class QAction;
class QMenu;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    bool showGrid;
    bool scaleToFit;

protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent* event);

private slots:
    void about();
    void gameLoop();
    void toggleScale();
    void toggleGrid();

private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void createWorld();
    void createWorldView();
    void createTimers();
    void readSettings();
    void writeSettings();

    World *world;
    WorldView *worldView;
    QTimer *gameTimer;
    PerformanceTimer *framerateTimer;
    PerformanceTimer *modelTimer;
    PerformanceTimer *viewTimer;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QMenu *optionsMenu;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *toggleScaleAct;
    QAction *toggleGridAct;
};

#endif // MAINWINDOW_H
