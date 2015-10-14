TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    qx \
    dxf \
    pgm \
    hpgl

pgm.depends = dxf
