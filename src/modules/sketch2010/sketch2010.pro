#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T01:03:48
#
#-------------------------------------------------

QT       += core gui xml

TARGET = sketch2010
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    SketchDrawing.cpp \
    SketchReader.cpp \
    SketchPlay.cpp

HEADERS += \
    Sketch.h \
    SketchDrawing.h \
    SketchReader.h \
    SketchPlay.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../shared.pri)
