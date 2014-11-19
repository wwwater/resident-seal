HEADERS += \
    mainwindow.h \
    particle.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    particle.cpp

TARGET = resident-seal 
DEPENDPATH += .
INCLUDEPATH += .

DESTDIR = ../bin/
MOC_DIR = ../build/
OBJECTS_DIR = ../build/
