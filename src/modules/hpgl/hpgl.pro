#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T18:34:59
#
#-------------------------------------------------

QT       += widgets opengl svg

TARGET = hpgl
TEMPLATE = lib
CONFIG += staticlib

DEFINES += HPGL_LIBRARY

SOURCES += \
    HpglDocument.cpp \
    HpglParser.cpp \
    HpglPaintable.cpp \
    HpglTextReader.cpp \
    HpglCommand.cpp

HEADERS += Hpgl.h\
        hpgl_global.h \
    HpglDocument.h \
    HpglParser.h \
    HpglPaintable.h \
    HpglTextReader.h \
    HpglCommand.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../shared.pri)
