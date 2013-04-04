QT += declarative
SOURCES += vplay.cpp qmlapplicationviewer.cpp
HEADERS += qmlapplicationviewer.h
RESOURCES = vplay.qrc
include(projectinclude.pri)

DEFINES += QML_PLATFORM_PATH=$$VPlayPluginsPlatformFolder.source
DEFINES += QML_GENERIC_PATH=$$VPlayPluginsGenericFolder.source

mac {
  CONFIG -= app_bundle
}
