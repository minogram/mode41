#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T19:04:19
#
#-------------------------------------------------

QT       += widgets opengl svg xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = qx
TEMPLATE = lib
CONFIG += staticlib

SOURCES += Qx.cpp \
    QXGraphicsPictureItem.cpp

HEADERS += Qx.h \
    QXGraphicsPictureItem.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../shared.pri)


