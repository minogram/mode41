#-------------------------------------------------
# wykobi.pro
#
# visit below sites to learn wykobi
# http://www.wykobi.com/
# http://www.codeproject.com/Articles/22568/Computational-Geometry-C-and-Wykobi
#-------------------------------------------------

QT       -= core gui

TARGET = wykobi
TEMPLATE = lib
CONFIG += staticlib

DEFINES += WYKOBI_LIBRARY

SOURCES += \
    wykobi.inl \
    wykobi_axis_projection_descriptor.inl \
    wykobi_clipping.inl \
    wykobi_duplicates.inl \
    wykobi_earclipping.inl \
    wykobi_hull.inl \
    wykobi_matrix.inl \
    wykobi_minimum_bounding_ball.inl \
    wykobi_naive_group_intersections.inl \
    wykobi_nd.inl \
    wykobi_normalization.inl \
    wykobi_ordered_polygon.inl \
    wykobi_build.cpp

HEADERS += \
    wykobi.hpp \
    wykobi_algorithm.hpp \
    wykobi_graphics_net.hpp \
    wykobi_graphics_opengl.hpp \
    wykobi_graphics_vcl.hpp \
    wykobi_gui.hpp \
    wykobi_instantiate.hpp \
    wykobi_math.hpp \
    wykobi_matrix.hpp \
    wykobi_nd.hpp \
    wykobi_utilities.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    release-notes.txt \
    wykobi_license.txt

include($$PWD/../../shared.pri)
