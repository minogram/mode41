#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T10:22:26
#
#-------------------------------------------------

QT       += core gui opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tailo
TEMPLATE = app

INCLUDEPATH += src dxf \
    ../3rdparty/wykobi

SOURCES += \
    src/main.cpp \
    src/PtnGraphicsView.cpp \
    src/PtnMainWindow.cpp \
    src/PtnModel.cpp \
    src/PtnMainWindow.Events.cpp \
    src/PtnMainWindow.File.cpp \
    src/PtnMainWindow.View.cpp \
    src/TAOptionsWidget.cpp \
    src/PtnMainWindow.Tools.cpp \
    src/DxfPtnConvert.cpp \
    src/PtnSceneBuilder.cpp \
    dxf/DxfModel.cpp \
    dxf/DxfSceneBuilder.cpp \
    dxf/DxfReader.cpp \
    dxf/DxfLineReader.cpp \
    src/PtnMainWindow.Debug.cpp \
    dxf/DxfModelReader.cpp \
#    wykobi/wykobi.inl \
#    wykobi/wykobi_axis_projection_descriptor.inl \
#    wykobi/wykobi_build.cpp \
#    wykobi/wykobi_clipping.inl \
#    wykobi/wykobi_duplicates.inl \
#    wykobi/wykobi_earclipping.inl \
#    wykobi/wykobi_hull.inl \
#    wykobi/wykobi_matrix.inl \
#    wykobi/wykobi_minimum_bounding_ball.inl \
#    wykobi/wykobi_naive_group_intersections.inl \
#    wykobi/wykobi_nd.inl \
#    wykobi/wykobi_normalization.inl \
#    wykobi/wykobi_ordered_polygon.inl

HEADERS  += \
    src/PtnGraphicsView.h \
    src/PtnMainWindow.h \
    src/PtnModel.h \
    src/TAOptionsWidget.h \
    src/QXUiBuilder.h \
    src/DxfPtnConvert.h \
    src/PtnSceneBuilder.h \
    dxf/DxfModel.h \
    dxf/DxfSceneBuilder.h \
    dxf/DxfReader.h \
    dxf/DxfLineReader.h \
    dxf/DxfModelReader.h \
#    wykobi/wykobi.hpp \
#    wykobi/wykobi_algorithm.hpp \
#    wykobi/wykobi_graphics_net.hpp \
#    wykobi/wykobi_graphics_opengl.hpp \
#    wykobi/wykobi_graphics_vcl.hpp \
#    wykobi/wykobi_gui.hpp \
#    wykobi/wykobi_instantiate.hpp \
#    wykobi/wykobi_math.hpp \
#    wykobi/wykobi_matrix.hpp \
#    wykobi/wykobi_nd.hpp \
#    wykobi/wykobi_utilities.hpp

DISTFILES += \
    Todo.txt \
    wykobi/wykobi_license.txt

RESOURCES += \
    res/icons.qrc \
    res/libreoffice/icons.qrc

# todo: only windows
RC_FILE = Tailo.rc

