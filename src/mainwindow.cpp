#include <QtGui>
#include "mainwindow.h"
#include "view.h"

MainWindow::MainWindow()
{
    setWindowTitle("Abode of Seals");
    createActions();
    createMenus();
    createStatusBar();
    readSettings();

    populateScene();


    View *view = new View("Main view");
    view->view()->setScene(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    // Set layout in QWidget
    QWidget *window = new QWidget();
    window->setLayout(layout);
    // Set QWidget as the central layout of the main window
    setCentralWidget(window);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void MainWindow::about()
{
    QMessageBox::about(
        this,
        "About Abode of Seals",
        "This app shows how to take care of cute seals and give them all the love they need. "
        "Don't forget to caress your seal!"
    );
}

void MainWindow::createActions()
{
    exitAct = new QAction("E&xit", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction("&About", this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("Ready");
}

void MainWindow::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene;
    /*
        QImage image("../resources/.png");

        // Populate scene
        int xx = 0;
        int nitems = 0;
        for (int i = -11000; i < 11000; i += 110) {
            ++xx;
            int yy = 0;
            for (int j = -7000; j < 7000; j += 70) {
                ++yy;
                qreal x = (i + 11000) / 22000.0;
                qreal y = (j + 7000) / 14000.0;

                QColor color(image.pixel(int(image.width() * x), int(image.height() * y)));
                QGraphicsItem *item = new Chip(color, xx, yy);
                item->setPos(QPointF(i, j));
                scene->addItem(item);

                ++nitems;
            }
        }*/
}
