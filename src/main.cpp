#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Aboud of Seals");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
