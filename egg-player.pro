TARGET = egg-player
TEMPLATE = app

include(egg-player.pri)

QT += \
    core \
    widgets \
    sql

INCLUDEPATH += \
    lib/bass-2.4/include \
    lib/taglib-1.11.1/include \
    src/config \
    src/core \
    src/core/threading \
    src/globals \
    src/ui \
    src/ui/components \
    src/ui/layouts \
    src/utils

LIBS += \
    -luser32 \
    -lshcore \
    -L"$$PWD/lib/bass-2.4/lib" -lbass

CONFIG(debug, debug|release) {
    LIBS += -L"$$PWD/lib/taglib-1.11.1/lib" -ltagd
    DESTDIR = $$PWD/bin/debug
}
CONFIG(release, debug|release) {
    LIBS += -L"$$PWD/lib/taglib-1.11.1/lib" -ltag
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
    src/config/config.hpp \
    src/config/configapp.hpp \
    src/config/configbar.hpp \
    src/config/configitem.hpp \
    src/config/configlibrary.hpp \
    src/config/configplayer.hpp \
    src/config/configshortcut.hpp \
    src/core/audio.hpp \
    src/core/cache.hpp \
    src/core/library.hpp \
    src/core/logger.hpp \
    src/core/player.hpp \
    src/core/shortcut.hpp \
    src/core/timer.hpp \
    src/core/threading/abstractthread.hpp \
    src/core/threading/audioloader.hpp \
    src/core/threading/cachebuilder.hpp \
    src/core/threading/threadpool.hpp \
    src/globals/constants.hpp \
    src/globals/types.hpp \
    src/ui/eggplayer.hpp \
    src/ui/musicbar.hpp \
    src/ui/musiclibrary.hpp \
    src/ui/components/clickableslider.hpp \
    src/ui/components/clickablestyle.hpp \
    src/ui/components/iconbutton.hpp \
    src/ui/components/rowhoverdelegate.hpp \
    src/ui/layouts/borderlayout.hpp \
    src/utils/colorutil.hpp \
    src/utils/fileutil.hpp \
    src/utils/util.hpp \
    src/utils/utils.hpp

SOURCES += \
    src/main.cpp \
    src/config/config.cpp \
    src/config/configapp.cpp \
    src/config/configbar.cpp \
    src/config/configitem.cpp \
    src/config/configlibrary.cpp \
    src/config/configplayer.cpp \
    src/config/configshortcut.cpp \
    src/core/audio.cpp \
    src/core/cache.cpp \
    src/core/library.cpp \
    src/core/logger.cpp \
    src/core/player.cpp \
    src/core/shortcut.cpp \
    src/core/timer.cpp \
    src/core/threading/abstractthread.cpp \
    src/core/threading/audioloader.cpp \
    src/core/threading/cachebuilder.cpp \
    src/core/threading/threadpool.cpp \
    src/globals/constants.cpp \
    src/ui/eggplayer.cpp \
    src/ui/musicbar.cpp \
    src/ui/musiclibrary.cpp \
    src/ui/components/clickableslider.cpp \
    src/ui/components/clickablestyle.cpp \
    src/ui/components/iconbutton.cpp \
    src/ui/components/rowhoverdelegate.cpp \
    src/ui/layouts/borderlayout.cpp \
    src/utils/colorutil.cpp \
    src/utils/fileutil.cpp \
    src/utils/util.cpp
