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
    src/core/audio.hpp \
    src/core/bass.hpp \
    src/core/basserror.hpp \
    src/core/bassstream.hpp \
    src/core/cache.hpp \
    src/core/constants.hpp \
    src/core/config.hpp \
    src/core/configabstract.hpp \
    src/core/configapp.hpp \
    src/core/configbar.hpp \
    src/core/configlibrary.hpp \
    src/core/configplayer.hpp \
    src/core/configshortcut.hpp \
    src/core/library.hpp \
    src/core/logger.hpp \
    src/core/player.hpp \
    src/core/shortcut.hpp \
    src/core/tag.hpp \
    src/threading/abstractthread.hpp \
    src/threading/threadpool.hpp \
    src/utils/colorutil.hpp \
    src/utils/fileutil.hpp \
    src/utils/util.hpp \
    src/widgets/eggwidget.hpp \
    src/widgets/barwidget.hpp \
    src/widgets/librarywidget.hpp \
    src/widgets/components/borderlayout.hpp \
    src/widgets/components/clickablestyle.hpp \
    src/widgets/components/colortransitionwidget.hpp \
    src/widgets/components/iconbutton.hpp \
    src/widgets/components/iconfactory.hpp \
    src/widgets/components/mainwindow.hpp \
    src/widgets/components/rowhoverdelegate.hpp \
    src/widgets/components/slider.hpp \
    src/widgets/components/smoothtablewidget.hpp \
    src/widgets/components/tablewidget.hpp \
    src/threading/audioloaderthread.hpp \
    src/threading/audioloaderworker.hpp \
    src/threading/coverloaderthread.hpp \
    src/threading/coverloaderworker.hpp

SOURCES += \
    src/main.cpp \
    src/core/audio.cpp \
    src/core/bass.cpp \
    src/core/basserror.cpp \
    src/core/bassstream.cpp \
    src/core/cache.cpp \
    src/core/constants.cpp \
    src/core/config.cpp \
    src/core/configabstract.cpp \
    src/core/configapp.cpp \
    src/core/configbar.cpp \
    src/core/configlibrary.cpp \
    src/core/configplayer.cpp \
    src/core/configshortcut.cpp \
    src/core/library.cpp \
    src/core/logger.cpp \
    src/core/player.cpp \
    src/core/shortcut.cpp \
    src/core/tag.cpp \
    src/threading/abstractthread.cpp \
    src/threading/threadpool.cpp \
    src/utils/colorutil.cpp \
    src/utils/fileutil.cpp \
    src/utils/util.cpp \
    src/widgets/eggwidget.cpp \
    src/widgets/barwidget.cpp \
    src/widgets/librarywidget.cpp \
    src/widgets/components/borderlayout.cpp \
    src/widgets/components/clickablestyle.cpp \
    src/widgets/components/colortransitionwidget.cpp \
    src/widgets/components/iconbutton.cpp \
    src/widgets/components/iconfactory.cpp \
    src/widgets/components/mainwindow.cpp \
    src/widgets/components/rowhoverdelegate.cpp \
    src/widgets/components/slider.cpp \
    src/widgets/components/smoothtablewidget.cpp \
    src/widgets/components/tablewidget.cpp \
    src/threading/audioloaderthread.cpp \
    src/threading/audioloaderworker.cpp \
    src/threading/coverloaderthread.cpp \
    src/threading/coverloaderworker.cpp

