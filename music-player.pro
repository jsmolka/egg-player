TARGET = music-player
TEMPLATE = app

QT += \
    core \
    widgets

# CONFIG += \
#    console

# INCLUDEPATH += \
#     externs/

HEADERS += \
    src/const/path.hpp \
    src/const/language.hpp \
    src/util/fileutil.hpp \
    src/gui/components/iconbutton.hpp

SOURCES += \
    src/main/main.cpp \
    src/const/path.cpp \
    src/const/language.cpp \
    src/util/fileutil.cpp \
    src/gui/components/iconbutton.cpp
