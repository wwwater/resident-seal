HEADERS += \
    mainwindow.h \
    view.h \
    particle.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    view.cpp \
    particle.cpp

TARGET = resident-seal 
DEPENDPATH += .
INCLUDEPATH += .

DESTDIR = ../bin/
MOC_DIR = ../build/
OBJECTS_DIR = ../build/
