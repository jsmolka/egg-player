TARGET = music-player
TEMPLATE = app

QT += \
    core \
    widgets \
    multimedia

INCLUDEPATH += \
    ext/taglib/include

LIBS += \
    -L"$$PWD/ext/taglib/lib" -ltag.dll

HEADERS += \
    src/constants/path.hpp \
    src/constants/language.hpp \
    src/core/audiofile.hpp \
    src/core/library.hpp \
    src/gui/components/iconbutton.hpp \
    src/utils/fileutil.hpp \
    src/utils/randutil.hpp \
    src/core/player.hpp

SOURCES += \
    src/constants/path.cpp \
    src/constants/language.cpp \
    src/core/audiofile.cpp \
    src/core/library.cpp \
    src/gui/components/iconbutton.cpp \
    src/utils/fileutil.cpp \
    src/utils/randutil.cpp \
    src/main.cpp \
    src/core/player.cpp
