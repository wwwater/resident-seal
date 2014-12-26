HEADERS += \
    performance_timer.h \
    mainwindow.h \
		seal.h \
    seal_view.h \
    terrain.h \
    terrain_view.h

SOURCES += \
    performance_timer.cpp \
    main.cpp \
    mainwindow.cpp \
		seal.cpp \
    seal_view.cpp \
    terrain.cpp \
    terrain_view.cpp

QMAKE_CXXFLAGS += -std=c++11 -fdiagnostics-color=always

QT += widgets

TARGET = resident-seal 
DEPENDPATH += .
INCLUDEPATH += .

DESTDIR = ../bin/
MOC_DIR = ../build/
OBJECTS_DIR = ../build/
