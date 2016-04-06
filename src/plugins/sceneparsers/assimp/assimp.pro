TARGET = assimpsceneio
QT += core-private 3dcore 3dcore-private 3drender 3drender-private 3dextras

include(../../../3rdparty/assimp/assimp_dependency.pri)

HEADERS += \
    assimphelpers.h \
    assimpio.h

SOURCES += \
    assimphelpers.cpp \
    main.cpp \
    assimpio.cpp

DISTFILES += \
    assimp.json

PLUGIN_TYPE = sceneparsers
PLUGIN_CLASS_NAME = AssimpSceneIOPlugin
load(qt_plugin)
