TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    qx \
    dxf \
    pgm \
    hpgl \
    sketch2010

pgm.depends = dxf
