TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = \
    3rdparty \
    modules \
    plugins \
    tailor \
    viewer \
    examples \

tailor.depends = modules
viewer.depends = modules
