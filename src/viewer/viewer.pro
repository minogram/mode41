#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T20:09:22
#
#-------------------------------------------------

QT       += core gui opengl printsupport svg

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

ROOTDIR = c:/dev

INCLUDEPATH += src \
    ../3rdparty/wykobi \
    ../3rdparty/freeimage/x32 \
    ../modules/qx \
    ../modules/dxf \
    ../modules/pgm \


LIBS += \
    -L$$ROOTDIR/mode41-build/src/modules/dxf/debug -ldxf \
    -L$$ROOTDIR/mode41-build/src/modules/qx/debug -lqx \
    -L$$ROOTDIR/mode41-build/src/modules/pgm/debug -lpgm \
    -L$$ROOTDIR/mode41/src/3rdparty/freeimage/x32 -lfreeimage \

release: DESTDIR = release
debug: DESTDIR = debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

