QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = music-player
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        src/main/main.cpp
