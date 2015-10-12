TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    3rdparty \
    modules \
    tailor \
    viewer \

tailor.depends = modules
viewer.depends = modules
