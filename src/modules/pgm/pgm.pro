#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T20:38:53
#
#-------------------------------------------------

QT       += widgets opengl svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = pgm
TEMPLATE = lib
CONFIG += staticlib

DEFINES += PGM_LIBRARY

SOURCES += Pgm.cpp \
    DxfPtnConvert.cpp \
    PtnModel.cpp \
    PtnSceneBuilder.cpp

HEADERS += Pgm.h\
    pgm_global.h \
    DxfPtnConvert.h \
    PtnModel.h \
    PtnSceneBuilder.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../shared.pri)


