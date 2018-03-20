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
    src/gui/components/iconbutton.hpp \
    src/utils/fileutil.hpp \
    src/utils/randutil.hpp

SOURCES += \
    src/constants/path.cpp \
    src/constants/language.cpp \
    src/core/audiofile.cpp \
    src/gui/components/iconbutton.cpp \
    src/utils/fileutil.cpp \
    src/main.cpp \
    src/utils/randutil.cpp
