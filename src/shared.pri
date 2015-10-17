########################
#
#   shared.pri
#
########################

# change below variable for your environment

SRC_DIR = c:/dev/mode41
BUILD_DIR = c:/dev/mode41-build

########################

INCLUDEPATH += src \
    $$SRC_DIR/src/3rdparty/cpplinq \
    $$SRC_DIR/src/3rdparty/freeimage/x32 \
    $$SRC_DIR/src/3rdparty/wykobi \
    $$SRC_DIR/src/modules/qx \
    $$SRC_DIR/src/modules/dxf \
    $$SRC_DIR/src/modules/pgm \
    $$SRC_DIR/src/modules/hpgl \
    $$SRC_DIR/src/modules/sketch2010 \

LIBS += \
    -L$$SRC_DIR/src/3rdparty/freeimage/x32 -lfreeimage \
    -L$$BUILD_DIR/src/modules/qx/debug -lqx \
    -L$$BUILD_DIR/src/modules/dxf/debug -ldxf \
    -L$$BUILD_DIR/src/modules/pgm/debug -lpgm \
    -L$$BUILD_DIR/src/modules/hpgl/debug -lhpgl \
    -L$$BUILD_DIR/src/modules/sketch2010/debug -lsketch2010 \

#LIBS += \
#    -L$$SRC_DIR/src/3rdparty/freeimage/x32 -lfreeimage \
#    -L$$BUILD_DIR/src/modules/qx/release -lqx \
#    -L$$BUILD_DIR/src/modules/dxf/release -ldxf \
#    -L$$BUILD_DIR/src/modules/pgm/release -lpgm \
#    -L$$BUILD_DIR/src/modules/hpgl/release -lhpgl \
#    -L$$BUILD_DIR/src/modules/sketch2010/release -lsketch2010 \


#########################

release: DESTDIR = release
debug: DESTDIR = debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

