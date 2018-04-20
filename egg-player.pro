TARGET = egg-player
TEMPLATE = app

RC_ICONS += \
    resource/images/egg/egg.ico

QT += \
    core \
    widgets \
    sql

INCLUDEPATH += \
    $$PWD/ext/bass-2.4/include \
    $$PWD/ext/taglib-1.11.1/include \
    $$PWD/src/constants \
    $$PWD/src/core \
    $$PWD/src/ui \
    $$PWD/src/ui/components \
    $$PWD/src/ui/layouts \
    $$PWD/src/utils

LIBS += \
    -L"$$PWD/ext/bass-2.4/lib" -lbass

CONFIG(debug, debug|release)
{
    LIBS += -L"$$PWD/ext/taglib-1.11.1/lib" -ltagd
    DESTDIR = $$PWD/bin/debug
}
CONFIG(release, debug|release)
{
    LIBS += -L"$$PWD/ext/taglib-1.11.1/lib" -ltag
    DESTDIR = $$PWD/bin/release
}

HEADERS += \
    $$PWD/src/core/audio.hpp \
    $$PWD/src/core/audiolist.hpp \
    $$PWD/src/core/cache.hpp \
    $$PWD/src/core/library.hpp \
    $$PWD/src/core/player.hpp \
    $$PWD/src/core/timer.hpp \
    $$PWD/src/constants/constants.hpp \
    $$PWD/src/ui/eggplayer.hpp \
    $$PWD/src/ui/musicbar.hpp \
    $$PWD/src/ui/musiclibrary.hpp \
    $$PWD/src/ui/components/iconbutton.hpp \
    $$PWD/src/ui/components/lengthslider.hpp \
    $$PWD/src/ui/components/songinfo.hpp \
    $$PWD/src/ui/layouts/borderlayout.hpp \
    $$PWD/src/utils/colorutil.hpp \
    $$PWD/src/utils/config.hpp \
    $$PWD/src/utils/fileutil.hpp \
    $$PWD/src/utils/logger.hpp

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/core/audio.cpp \
    $$PWD/src/core/audiolist.cpp \
    $$PWD/src/core/cache.cpp \
    $$PWD/src/core/library.cpp \
    $$PWD/src/core/player.cpp \
    $$PWD/src/core/timer.cpp \
    $$PWD/src/constants/constants.cpp \
    $$PWD/src/ui/eggplayer.cpp \
    $$PWD/src/ui/musicbar.cpp \
    $$PWD/src/ui/musiclibrary.cpp \
    $$PWD/src/ui/components/iconbutton.cpp \
    $$PWD/src/ui/components/lengthslider.cpp \
    $$PWD/src/ui/components/songinfo.cpp \
    $$PWD/src/ui/layouts/borderlayout.cpp \
    $$PWD/src/utils/colorutil.cpp \
    $$PWD/src/utils/config.cpp \
    $$PWD/src/utils/fileutil.cpp \
    $$PWD/src/utils/logger.cpp
