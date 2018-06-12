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
    src/core \
    src/core/threading \
    src/globals \
    src/utils \
    src/utils/config \
    src/widgets \
    src/widgets/components \
    src/widgets/layouts

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
    src/core/audio.hpp \
    src/core/cache.hpp \
    src/core/library.hpp \
    src/core/player.hpp \
    src/core/timer.hpp \
    src/core/threading/abstractthread.hpp \
    src/core/threading/audioloader.hpp \
    src/core/threading/cachebuilder.hpp \
    src/core/threading/threadpool.hpp \
    src/globals/constants.hpp \
    src/globals/types.hpp \
    src/utils/colorutil.hpp \
    src/utils/fileutil.hpp \
    src/utils/logger.hpp \
    src/utils/shortcut.hpp \
    src/utils/util.hpp \
    src/utils/config/config.hpp \
    src/utils/config/configapp.hpp \
    src/utils/config/configbar.hpp \
    src/utils/config/configitem.hpp \
    src/utils/config/configlibrary.hpp \
    src/utils/config/configplayer.hpp \
    src/utils/config/configshortcut.hpp \
    src/widgets/eggplayer.hpp \
    src/widgets/musicbar.hpp \
    src/widgets/musiclibrary.hpp \
    src/widgets/components/clickableslider.hpp \
    src/widgets/components/clickablestyle.hpp \
    src/widgets/components/iconbutton.hpp \
    src/widgets/components/rowhoverdelegate.hpp \
    src/widgets/layouts/borderlayout.hpp

SOURCES += \
    src/main.cpp \
    src/core/audio.cpp \
    src/core/cache.cpp \
    src/core/library.cpp \
    src/core/player.cpp \
    src/core/timer.cpp \
    src/core/threading/abstractthread.cpp \
    src/core/threading/audioloader.cpp \
    src/core/threading/cachebuilder.cpp \
    src/core/threading/threadpool.cpp \
    src/globals/constants.cpp \
    src/utils/colorutil.cpp \
    src/utils/fileutil.cpp \
    src/utils/logger.cpp \
    src/utils/shortcut.cpp \
    src/utils/util.cpp \
    src/utils/config/config.cpp \
    src/utils/config/configapp.cpp \
    src/utils/config/configbar.cpp \
    src/utils/config/configitem.cpp \
    src/utils/config/configlibrary.cpp \
    src/utils/config/configplayer.cpp \
    src/utils/config/configshortcut.cpp \
    src/widgets/eggplayer.cpp \
    src/widgets/musicbar.cpp \
    src/widgets/musiclibrary.cpp \
    src/widgets/components/clickableslider.cpp \
    src/widgets/components/clickablestyle.cpp \
    src/widgets/components/iconbutton.cpp \
    src/widgets/components/rowhoverdelegate.cpp \
    src/widgets/layouts/borderlayout.cpp
