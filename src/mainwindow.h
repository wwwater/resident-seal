#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *exitAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
