#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T20:09:22
#
#-------------------------------------------------

QT       += core gui opengl printsupport svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Viewer
TEMPLATE = app

SOURCES += \
    main.cpp\
    MainWindow.cpp \
    MainWindow.File.cpp \
    ViewerView.cpp \
    MainWindow.View.cpp \
    MainWindow.Events.cpp \
    FreeImage2QImage.cpp

HEADERS  += \
    MainWindow.h \
    ViewerView.h \
    FreeImage2QImage.h

# TODO
QTPLUGIN += psd

# TODO:
PRE_TARGETDEPS += \
    C:\dev\mode41-build\src\modules\dxf\debug\dxf.lib \
    C:\dev\mode41-build\src\modules\hpgl\debug\hpgl.lib \
    C:\dev\mode41-build\src\modules\sketch2010\debug\sketch2010.lib \

viewer.depends = dxf hpgl

include($$PWD/../../shared.pri)


