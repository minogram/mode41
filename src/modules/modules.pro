TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    qx \
    dxf \
    pgm \

pgm.depends = dxf
