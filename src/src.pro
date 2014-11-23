HEADERS += \
    fps_counter.h \
    mainwindow.h \
    particle.h

SOURCES += \
    fps_counter.cpp \
    main.cpp \
    mainwindow.cpp \
    particle.cpp

QMAKE_CXXFLAGS += -std=c++11 -fdiagnostics-color=always

TARGET = resident-seal 
DEPENDPATH += .
INCLUDEPATH += .

DESTDIR = ../bin/
MOC_DIR = ../build/
OBJECTS_DIR = ../build/
