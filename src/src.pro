HEADERS += \
    performance_timer.h \
    mainwindow.h \
    seal_view.h

SOURCES += \
    performance_timer.cpp \
    main.cpp \
    mainwindow.cpp \
    seal_view.cpp

QMAKE_CXXFLAGS += -std=c++11 -fdiagnostics-color=always

TARGET = resident-seal 
DEPENDPATH += .
INCLUDEPATH += .

DESTDIR = ../bin/
MOC_DIR = ../build/
OBJECTS_DIR = ../build/
