#include <QtGui>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
    createStatusBar();
    readSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (1) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::about()
{
    QMessageBox::about(
        this,
        tr("About Application"),
        tr("The <b>Application</b> example demonstrates how to "
           "take care of cute seals and give them all love they need. "
           "Don't forget to caress your seal!"));
}

void MainWindow::createActions()
{
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Leave the seals"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readSettings()
{
    QSettings settings("Trolltech", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings("Trolltech", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
