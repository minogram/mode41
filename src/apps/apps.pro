TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    tailor \
    viewer \

tailor.depends = modules
viewer.depends = modules
