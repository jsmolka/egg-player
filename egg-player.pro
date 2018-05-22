TARGET = egg-player
TEMPLATE = app

include(egg-player.pri)

QT += \
    core \
    widgets \
    sql

INCLUDEPATH += \
    $$PWD/ext/bass-2.4/include \
    $$PWD/ext/taglib-1.11.1/include \
    $$PWD/src/core \
    $$PWD/src/core/threading \
    $$PWD/src/globals \
    $$PWD/src/ui \
    $$PWD/src/ui/components \
    $$PWD/src/ui/layouts \
    $$PWD/src/utils

LIBS += \
    -luser32 \
    -lshcore \
    -L"$$PWD/ext/bass-2.4/lib" -lbass

CONFIG(debug, debug|release) {
    LIBS += -L"$$PWD/ext/taglib-1.11.1/lib" -ltagd
    DESTDIR = $$PWD/bin/debug
}
CONFIG(release, debug|release) {
    LIBS += -L"$$PWD/ext/taglib-1.11.1/lib" -ltag
    DESTDIR = $$PWD/bin/release

    QMAKE_CFLAGS_RELEASE -= -O
    QMAKE_CFLAGS_RELEASE -= -O1
    QMAKE_CFLAGS_RELEASE *= -O2

    QMAKE_CXXFLAGS_RELEASE -= -O
    QMAKE_CXXFLAGS_RELEASE -= -O1
    QMAKE_CXXFLAGS_RELEASE *= -O2
}

RESOURCES = egg-player.qrc

HEADERS += \
    $$PWD/src/core/audio.hpp \
    $$PWD/src/core/cache.hpp \
    $$PWD/src/core/library.hpp \
    $$PWD/src/core/player.hpp \
    $$PWD/src/core/timer.hpp \
    $$PWD/src/core/threading/abstractthread.hpp \
    $$PWD/src/core/threading/audioloader.hpp \
    $$PWD/src/core/threading/cachebuilder.hpp \
    $$PWD/src/core/threading/threadpool.hpp \
    $$PWD/src/globals/constants.hpp \
    $$PWD/src/globals/types.hpp \
    $$PWD/src/ui/eggplayer.hpp \
    $$PWD/src/ui/musicbar.hpp \
    $$PWD/src/ui/musiclibrary.hpp \
    $$PWD/src/ui/components/clickableslider.hpp \
    $$PWD/src/ui/components/clickablestyle.hpp \
    $$PWD/src/ui/components/iconbutton.hpp \
    $$PWD/src/ui/components/rowhoverdelegate.hpp \
    $$PWD/src/ui/layouts/borderlayout.hpp \
    $$PWD/src/utils/config.hpp \
    $$PWD/src/utils/logger.hpp \
    $$PWD/src/utils/shortcut.hpp \
    $$PWD/src/utils/utils.hpp

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/core/audio.cpp \
    $$PWD/src/core/cache.cpp \
    $$PWD/src/core/library.cpp \
    $$PWD/src/core/player.cpp \
    $$PWD/src/core/timer.cpp \
    $$PWD/src/core/threading/abstractthread.cpp \
    $$PWD/src/core/threading/audioloader.cpp \
    $$PWD/src/core/threading/cachebuilder.cpp \
    $$PWD/src/core/threading/threadpool.cpp \
    $$PWD/src/globals/constants.cpp \
    $$PWD/src/ui/eggplayer.cpp \
    $$PWD/src/ui/musicbar.cpp \
    $$PWD/src/ui/musiclibrary.cpp \
    $$PWD/src/ui/components/clickableslider.cpp \
    $$PWD/src/ui/components/clickablestyle.cpp \
    $$PWD/src/ui/components/iconbutton.cpp \
    $$PWD/src/ui/components/rowhoverdelegate.cpp \
    $$PWD/src/ui/layouts/borderlayout.cpp \
    $$PWD/src/utils/config.cpp \
    $$PWD/src/utils/logger.cpp \
    $$PWD/src/utils/shortcut.cpp \
    $$PWD/src/utils/utils.cpp
