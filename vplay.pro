QT += declarative
SOURCES += vplay.cpp qmlapplicationviewer.cpp
HEADERS += qmlapplicationviewer.h
include(projectinclude.pri)

mac {
  CONFIG -= app_bundle
}
