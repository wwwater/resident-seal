#include "mainwindow.h"
#include "particle.h"

MainWindow::MainWindow()
{
    setWindowTitle("Abode of Seals");
    setMaximumSize(640, 480);
    setMinimumSize(250, 250);

    readSettings();
    createActions();
    createMenus();
    createGameView();
    createTimers();
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

void MainWindow::gameLoop()
{
    gameScene->advance();
    statusBar()->showMessage("FPS: " + QString::number(fpsCounter->tick(), 'g', 2));
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

void MainWindow::createGameView()
{
    gameScene = new QGraphicsScene();
    // Scenes are infinite, but Qt can better optimize performance when the size is constrained.
    gameScene->setSceneRect(0, 0, 400, 300);
    // Disable indexing of item positions for better performance.
    gameScene->setItemIndexMethod(QGraphicsScene::NoIndex);

    for (int i = 0; i < 20; i++) {
        Particle *baby = new Particle;
        baby->setPos(200, 150);
        gameScene->addItem(baby);
    }

    gameView = new QGraphicsView(gameScene);
    gameView->setRenderHint(QPainter::Antialiasing);
    gameView->setBackgroundBrush(Qt::black);
    gameView->setFrameShape(QFrame::NoFrame);
    setCentralWidget(gameView);
}

void MainWindow::createTimers()
{
    fpsCounter = new FPSCounter();
    gameTimer = new QTimer();
    QObject::connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    gameTimer->start(16);
}
