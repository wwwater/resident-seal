#include "mainwindow.h"
#include "seal_view.h"
#include "terrain.h"
#include "terrain_view.h"

MainWindow::MainWindow()
{
    setWindowTitle("Abode of Seals");
    // TODO: set setMaximumSize() to the size of the map, and make the window
    // as large as possible without exceeding desktop size.
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

    framerateStopwatch->lap();
    statusBar()->showMessage("FPS: " + framerateStopwatch->getAverageFrequencyAsString());
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
    Terrain terrain;
    terrain.loadFromFile(QString("../resources/terrain-map.json"));
    terrain.loadObstaclesFromFile(QString("../resources/terrain-obstacles.json"));

    int mapRows = terrain.height;
    int mapCols = terrain.width;
    int tileSize = 32;

    gameScene = new QGraphicsScene();
    // Scenes are infinite, but Qt can better optimize performance when the size is constrained.
    gameScene->setSceneRect(0, 0, mapCols * tileSize, mapRows * tileSize);
    // Disable indexing of item positions for better performance.
    gameScene->setItemIndexMethod(QGraphicsScene::NoIndex);

    TerrainView *terrainView = new TerrainView(mapRows, mapCols);
    for (int row = 0; row < mapRows; row++) {
        for (int col = 0; col < mapCols; col++) {
            terrainView->setTile(row, col, terrain.getTile(row, col));
        }
    }
    gameScene->addItem(terrainView);

    for (int i = 0; i < 200; i++) {
        SealView *baby = new SealView;
        baby->setDirection(qrand());
				std::vector <int> availableTiles; //array of non-obstacle tiles which contains indexes of these tiles
				//idx = r * Nc + c; c = idx % Nc, r = (idx - c) / Nc 
				for (int idx = 0; idx < mapRows * mapCols; ++idx) {
						int c = idx % mapCols; //convert idx to column and row
						int r = (idx - c) / mapCols;
						if (!terrain.isObstacle(r, c)) availableTiles.push_back(idx);
				}
				int babyPositionIdx = qrand() % availableTiles.size();
				int babyCol = availableTiles.at(babyPositionIdx) % mapCols; //convert idx to column and row
				int babyRow = (availableTiles.at(babyPositionIdx) - babyCol)  / mapCols; 
        baby->setPos(babyCol * tileSize, babyRow * tileSize);
        gameScene->addItem(baby);
    }

    gameView = new QGraphicsView(gameScene);
    gameView->setCacheMode(QGraphicsView::CacheBackground);
    gameView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    gameView->setBackgroundBrush(Qt::black);
    gameView->setFrameShape(QFrame::NoFrame);
    setCentralWidget(gameView);
}

void MainWindow::createTimers()
{
    framerateStopwatch = new PerformanceTimer();
    framerateStopwatch->start();

    gameTimer = new QTimer();
    QObject::connect(gameTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    gameTimer->start(160);
}
