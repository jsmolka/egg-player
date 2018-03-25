TARGET = egg-player
TEMPLATE = app

RC_ICONS += \
    data/images/egg/egg.ico

QT += \
    core \
    widgets \
    multimedia

INCLUDEPATH += \
    ext/taglib/include

LIBS += \
    -L"$$PWD/ext/taglib/lib" -ltag.dll

HEADERS += \
    src/constants/language.hpp \
    src/constants/path.hpp \
    src/core/audio.hpp \
    src/core/audiolist.hpp \
    src/core/library.hpp \
    src/core/player.hpp \
    src/ui/components/iconbutton.hpp \
    src/ui/components/songinfo.hpp \
    src/ui/layouts/borderlayout.hpp \
    src/ui/mainwindow.hpp \
    src/ui/songlist.hpp \
    src/utils/fileutil.hpp \
    src/utils/randutil.hpp

SOURCES += \
    src/main.cpp \
    src/constants/language.cpp \
    src/constants/path.cpp \
    src/core/audio.cpp \
    src/core/audiolist.cpp \
    src/core/library.cpp \
    src/core/player.cpp \
    src/ui/components/iconbutton.cpp \
    src/ui/components/songinfo.cpp \
    src/ui/layouts/borderlayout.cpp \
    src/ui/mainwindow.cpp \
    src/ui/songlist.cpp \
    src/utils/fileutil.cpp \
    src/utils/randutil.cpp
