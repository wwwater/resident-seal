#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Seal Adoration Society");
    app.setApplicationName("Abode of Seals");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
