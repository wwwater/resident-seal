#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

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

private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void createGameView();
    void readSettings();
    void writeSettings();

    QGraphicsView *gameView;
    QGraphicsScene *gameScene;
    QTimer *gameTimer;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
