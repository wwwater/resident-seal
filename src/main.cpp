#include <QApplication>

 #include "mainwindow.h"

 int main(int argc, char *argv[])
 {
     //Q_INIT_RESOURCE(application); Didnt compile with this thing, no idea what it is for

     QApplication app(argc, argv);
     //app.setOrganizationName("Trolltech");
     app.setApplicationName("Aboud of Seals");
     MainWindow mainWin;
     mainWin.show();
     return app.exec();
 }
