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

#release: DESTDIR = release
#debug: DESTDIR = debug

#OBJECTS_DIR = $$DESTDIR/.obj
#MOC_DIR = $$DESTDIR/.moc
#RCC_DIR = $$DESTDIR/.qrc
#UI_DIR = $$DESTDIR/.ui

