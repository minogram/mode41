#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T00:53:22
#
#-------------------------------------------------

QT       -= gui

TARGET = freeimage
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS +=
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    freeimage-license.txt
