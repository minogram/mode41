#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T18:34:59
#
#-------------------------------------------------

QT += widgets opengl svg

TARGET = hpgl
TEMPLATE = lib
CONFIG += staticlib

DEFINES += HPGL_LIBRARY

SOURCES += \
    HpglDocument.cpp \
    HpglCommand.cpp \
    HpglReader.cpp \
    HpglReference.cpp \
    HpglCommandInfo.cpp \
    HpglState.cpp \
    HpglPlay.cpp \
    HpglPainterPlay.cpp

HEADERS += \
    Hpgl.h\
    HpglDocument.h \
    HpglCommand.h \
    HpglReader.h \
    HpglReference.h \
    HpglCommandInfo.h \
    HpglDocument_p.h \
    HpglCommand_p.h \
    HpglState.h \
    HpglPlay.h \
    HpglPainterPlay.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += \
    ../../3rdparty/wykobi \
    ../../3rdparty/cpplinq \

include($$PWD/../../shared.pri)
