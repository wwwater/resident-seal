HEADERS += \
    fog.h \
    fog_view.h \
    mainwindow.h \
    performance_timer.h \
	seal.h \
    seal_view.h \
    terrain.h \
    terrain_view.h \
    utils.h \
    world.h

SOURCES += \
    fog.cpp \
    fog_view.cpp \
    main.cpp \
    performance_timer.cpp \
    mainwindow.cpp \
	seal.cpp \
    seal_view.cpp \
    terrain.cpp \
    terrain_view.cpp \
    utils.cpp \
    world.cpp

QMAKE_CXXFLAGS += -std=c++11 -fdiagnostics-color=always

QT += widgets

TARGET = resident-seal 
DEPENDPATH += .
INCLUDEPATH += .

DESTDIR = ../bin/
MOC_DIR = ../build/
OBJECTS_DIR = ../build/
