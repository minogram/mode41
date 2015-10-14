#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T11:54:38
#
#-------------------------------------------------

QT = core gui
TEMPLATE = lib
CONFIG += plugin
TARGET = psd
#PLUGIN_TYPE = imageformats

TARGET = psd

INCLUDEPATH += c:/dev/mode41/src/3rdparty/freeimage/x32

LIBS = -Lc:/dev/mode41/src/3rdparty/freeimage/x32 -lfreeimage

SOURCES += \
    QFreeImage.cpp \
    PsdHandler.cpp \
    PsdPlugin.cpp

HEADERS += \
    QFreeImage.h \
    PsdHandler.h

OTHER_FILES += pds.json
