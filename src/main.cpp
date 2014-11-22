#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Seal Adoration Society");
    app.setApplicationName("Abode of Seals");

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
