#include "mainwindow.h"
#include "seal_view.h"
#include "terrain.h"
#include "terrain_view.h"
#include "fog_view.h"
#include "seal.h"
#include "utils.h"
#include <list>

MainWindow::MainWindow()
{
    setWindowTitle("Abode of Seals");
    // TODO: set setMaximumSize() to the size of the map, and make the window
    // as large as possible without exceeding desktop size.
    setMinimumSize(250, 250);

    readSettings();
    createActions();
    createMenus();
    createWorld();
    createWorldView();
    createTimers();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if (this->scaleToFitEnabled) {
        this->worldView->scaleToFit();
    }
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

void MainWindow::toggleGrid()
{
    this->gridEnabled = !this->gridEnabled;
    this->worldView->toggleGrid(this->gridEnabled);
}

void MainWindow::toggleFog()
{
    this->fogEnabled = !this->fogEnabled;
    this->worldView->toggleFog(this->fogEnabled);
}

void MainWindow::toggleScaleToFit()
{
    this->scaleToFitEnabled = !this->scaleToFitEnabled;
    if (this->scaleToFitEnabled) {
        this->worldView->scaleToFit();
    } else {
        this->worldView->resetScale();
    }
}

void MainWindow::toggleHyperspeed()
{
    this->hyperspeedEnabled = !this->hyperspeedEnabled;
}

void MainWindow::gameLoop()
{
    modelTimer->reset();
    int worldUpdatesPerFrame = this->hyperspeedEnabled ? 10 : 1;
    for (int i = 0; i < worldUpdatesPerFrame; i++) {
        world->advance();
    }
    modelTimer->lap();

    viewTimer->reset();
    worldView->advance();
    viewTimer->lap();

    framerateTimer->lap();
    statusBar()->showMessage(
        "Frame: "     + framerateTimer->getAverageTimeAsString() +
        " | Models: " + modelTimer->getAverageTimeAsString() +
        " | Views: "  + viewTimer->getAverageTimeAsString() +
        " | Paint: "  + worldView->getAveragePaintTimeAsString());
}

void MainWindow::createActions()
{
    exitAct = new QAction("E&xit", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction("&About", this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    toggleFogAct = new QAction("Show fog", this);
    toggleFogAct->setCheckable(true);
    toggleFogAct->setChecked(this->fogEnabled);
    connect(toggleFogAct, SIGNAL(triggered()), this, SLOT(toggleFog()));

    toggleGridAct = new QAction("Show grid", this);
    toggleGridAct->setCheckable(true);
    toggleGridAct->setChecked(this->gridEnabled);
    connect(toggleGridAct, SIGNAL(triggered()), this, SLOT(toggleGrid()));

    toggleScaleToFitAct = new QAction("Scale to fit", this);
    toggleScaleToFitAct->setCheckable(true);
    toggleScaleToFitAct->setChecked(this->scaleToFitEnabled);
    connect(toggleScaleToFitAct, SIGNAL(triggered()), this, SLOT(toggleScaleToFit()));

    toggleHyperspeedAct = new QAction("10x speed", this);
    toggleHyperspeedAct->setCheckable(true);
    toggleHyperspeedAct->setChecked(this->hyperspeedEnabled);
    connect(toggleHyperspeedAct, SIGNAL(triggered()), this, SLOT(toggleHyperspeed()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAct);

    optionsMenu = menuBar()->addMenu("&Options");
    optionsMenu->addAction(toggleFogAct);
    optionsMenu->addAction(toggleGridAct);
    optionsMenu->addAction(toggleScaleToFitAct);
    optionsMenu->addAction(toggleHyperspeedAct);

    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAct);
}

void MainWindow::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    this->fogEnabled = settings.value("show_fog", true).toBool();
    this->gridEnabled = settings.value("show_grid", false).toBool();
    this->scaleToFitEnabled = settings.value("scale_to_fit", false).toBool();
    this->hyperspeedEnabled = settings.value("hyperspeed", false).toBool();
    resize(size);
    move(pos);
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("show_fog", this->fogEnabled);
    settings.setValue("show_grid", this->gridEnabled);
    settings.setValue("scale_to_fit", this->scaleToFitEnabled);
    settings.setValue("hyperspeed", this->hyperspeedEnabled);
}

void MainWindow::createWorld()
{
    Terrain *terrain = new Terrain();
    terrain->loadFromFile(QString("../resources/terrain-map.json"));
    terrain->loadObstaclesFromFile(QString("../resources/terrain-obstacles.json"));
    this->world = new World(terrain);
    
    int k = 6; // how many seals one wants
    int n = 0; // counter of available cells seen so far
    std::list<Cell> cellsForSeals;
    for (int row = 0; row < terrain->height; ++ row) {
        for (int col = 0; col < terrain->width; ++col) {
            Cell cell = Cell(row, col);
            if (!this->world->hasObstacleAt(cell)) {
                ++n;
                if (n <= k) {
                    cellsForSeals.push_back(cell);
                } else {
                    int r = qrand() % n;
                    if (r < k) {
                        auto toErase = cellsForSeals.begin();
                        std::advance(toErase, r);
                        cellsForSeals.erase(toErase);
                        cellsForSeals.push_back(cell);
                    }
                }
            }    
        }
    }

    for (Cell cell: cellsForSeals) {
        this->world->addSeal(new Seal(this->world, cell, qrand() % 8));
    }
}

void MainWindow::createWorldView()
{
    this->worldView = new WorldView(this->world);
    this->worldView->toggleFog(this->fogEnabled);
    this->worldView->toggleGrid(this->gridEnabled);
    if (this->scaleToFitEnabled) {
        this->worldView->scaleToFit();
    }
    this->setCentralWidget(this->worldView->widget);
}

void MainWindow::createTimers()
{
    modelTimer = new PerformanceTimer();
    viewTimer = new PerformanceTimer();
    framerateTimer = new PerformanceTimer();
    framerateTimer->start();

    gameTimer = new QTimer();
    QObject::connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    gameTimer->start(16);
}
