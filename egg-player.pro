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
    src/common \
    src/core \
    src/threading \
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
    src/common/constants.hpp \
    src/core/audio.hpp \
    src/core/bass.hpp \
    src/core/basserror.hpp \
    src/core/bassstream.hpp \
    src/core/cache.hpp \
    src/core/library.hpp \
    src/core/player.hpp \
    src/threading/abstractthread.hpp \
    src/threading/audioloader.hpp \
    src/threading/cachebuilder.hpp \
    src/threading/threadpool.hpp \
    src/utils/colorutil.hpp \
    src/utils/fileutil.hpp \
    src/utils/logger.hpp \
    src/utils/shortcut.hpp \
    src/utils/util.hpp \
    src/utils/config/config.hpp \
    src/utils/config/configabstract.hpp \
    src/utils/config/configapp.hpp \
    src/utils/config/configbar.hpp \
    src/utils/config/configlibrary.hpp \
    src/utils/config/configplayer.hpp \
    src/utils/config/configshortcut.hpp \
    src/widgets/eggwidget.hpp \
    src/widgets/barwidget.hpp \
    src/widgets/librarywidget.hpp \
    src/widgets/components/clickablestyle.hpp \
    src/widgets/components/iconbutton.hpp \
    src/widgets/components/mainwindow.hpp \
    src/widgets/components/rowhoverdelegate.hpp \
    src/widgets/components/slider.hpp \
    src/widgets/components/tablewidget.hpp \
    src/widgets/layouts/borderlayout.hpp

SOURCES += \
    src/main.cpp \
    src/common/constants.cpp \
    src/core/audio.cpp \
    src/core/bass.cpp \
    src/core/basserror.cpp \
    src/core/bassstream.cpp \
    src/core/cache.cpp \
    src/core/library.cpp \
    src/core/player.cpp \
    src/threading/abstractthread.cpp \
    src/threading/audioloader.cpp \
    src/threading/cachebuilder.cpp \
    src/threading/threadpool.cpp \
    src/utils/colorutil.cpp \
    src/utils/fileutil.cpp \
    src/utils/logger.cpp \
    src/utils/shortcut.cpp \
    src/utils/util.cpp \
    src/utils/config/config.cpp \
    src/utils/config/configabstract.cpp \
    src/utils/config/configapp.cpp \
    src/utils/config/configbar.cpp \
    src/utils/config/configlibrary.cpp \
    src/utils/config/configplayer.cpp \
    src/utils/config/configshortcut.cpp \
    src/widgets/barwidget.cpp \
    src/widgets/eggwidget.cpp \
    src/widgets/librarywidget.cpp \
    src/widgets/components/clickablestyle.cpp \
    src/widgets/components/iconbutton.cpp \
    src/widgets/components/mainwindow.cpp \
    src/widgets/components/rowhoverdelegate.cpp \
    src/widgets/components/slider.cpp \
    src/widgets/components/tablewidget.cpp \
    src/widgets/layouts/borderlayout.cpp
