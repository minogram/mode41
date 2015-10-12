#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T10:22:26
#
#-------------------------------------------------

QT       += core gui opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tailor
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/PtnGraphicsView.cpp \
    src/TAOptionsWidget.cpp \
    src/MainWindow.cpp \
    src/MainWindow.Debug.cpp \
    src/MainWindow.Events.cpp \
    src/MainWindow.File.cpp \
    src/MainWindow.Tools.cpp \
    src/MainWindow.View.cpp

HEADERS  += \
    src/PtnGraphicsView.h \
    src/TAOptionsWidget.h \
    src/QXUiBuilder.h \
    src/MainWindow.h

RESOURCES += \
    res/icons.qrc \
    res/libreoffice/icons.qrc

DISTFILES += \
    Todo.txt

# todo: only windows
RC_FILE = Tailor.rc

ROOTDIR = c:/dev

INCLUDEPATH += src \
    ../3rdparty/wykobi \
    ../modules/qx \
    ../modules/dxf \
    ../modules/pgm \

LIBS += \
    -L$$ROOTDIR/mode41-build/src/modules/dxf/debug -ldxf \
    -L$$ROOTDIR/mode41-build/src/modules/qx/debug -lqx \
    -L$$ROOTDIR/mode41-build/src/modules/pgm/debug -lpgm \

release: DESTDIR = release
debug: DESTDIR = debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

