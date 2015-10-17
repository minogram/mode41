#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T01:03:48
#
#-------------------------------------------------

QT       += widgets opengl svg xml xmlpatterns

TARGET = sketch2010
TEMPLATE = lib
CONFIG += staticlib

SOURCES += Sketch2010.cpp \
    SketchModel.cpp

HEADERS += Sketch2010.h \
    SketchModel.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../shared.pri)
