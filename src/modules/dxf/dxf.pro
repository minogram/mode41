#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T19:15:12
#
#-------------------------------------------------

QT       += widgets

TARGET = dxf
TEMPLATE = lib
CONFIG += staticlib

DEFINES += DXF_LIBRARY

SOURCES += Dxf.cpp \
    DxfLineReader.cpp \
    DxfModel.cpp \
    DxfModelReader.cpp \
    DxfReader.cpp \
    DxfSceneBuilder.cpp

HEADERS += Dxf.h\
        dxf_global.h \
    DxfLineReader.h \
    DxfModel.h \
    DxfModelReader.h \
    DxfReader.h \
    DxfSceneBuilder.h

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
