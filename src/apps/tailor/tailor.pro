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

include($$PWD/../../shared.pri)

