#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/qwidget.h>
#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(QGraphicsScene)
QT_FORWARD_DECLARE_CLASS(QGraphicsView)
QT_FORWARD_DECLARE_CLASS(QSlider)


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
    void readSettings();
    void writeSettings();
    void setupMatrix();
    void populateScene();
    
    QGraphicsScene *scene;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
