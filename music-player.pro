TARGET = music-player
TEMPLATE = app

QT += \
    core \
    widgets

# CONFIG += \
#    console

# INCLUDEPATH += \
#     ext/

HEADERS += \
    src/constants/path.hpp \
    src/constants/language.hpp \
    src/gui/components/iconbutton.hpp \
    src/utils/fileutil.hpp

SOURCES += \
    src/main.cpp \
    src/constants/path.cpp \
    src/constants/language.cpp \
    src/gui/components/iconbutton.cpp \
    src/utils/fileutil.cpp
