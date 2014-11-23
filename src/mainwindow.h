#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "fps_counter.h"

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
    void createGameView();
    void createTimers();
    void readSettings();
    void writeSettings();

    QGraphicsView *gameView;
    QGraphicsScene *gameScene;
    QTimer *gameTimer;
    FPSCounter *fpsCounter;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
