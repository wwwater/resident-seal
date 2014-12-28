#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "performance_timer.h"
#include "world.h"

class QAction;
class QMenu;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void about();
    void gameLoop();

private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void createWorld();
    void createWorldView();
    void createTimers();
    void readSettings();
    void writeSettings();

    QGraphicsView *gameView;
    QGraphicsScene *gameScene;
    World *world;
    QTimer *gameTimer;
    PerformanceTimer *framerateStopwatch;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
