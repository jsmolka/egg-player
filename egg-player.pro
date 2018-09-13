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
    src/core/bass \
    src/core/config \
    src/threading \
    src/threading/base \
    src/widgets \
    src/widgets/components

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

    QMAKE_CFLAGS_RELEASE -= /O1
    QMAKE_CFLAGS_RELEASE *= /O2
    QMAKE_CXXFLAGS_RELEASE -= /O1
    QMAKE_CXXFLAGS_RELEASE *= /O2
}

RESOURCES = egg-player.qrc

DEFINES *= QT_USE_QSTRINGBUILDER

HEADERS += \
    src/core/audio.hpp \
    src/core/bass/bass.hpp \
    src/core/bass/basserror.hpp \
    src/core/bass/bassstream.hpp \
    src/core/cache.hpp \
    src/core/constants.hpp \
    src/core/config/config.hpp \
    src/core/config/configapp.hpp \
    src/core/config/configbar.hpp \
    src/core/config/configlibrary.hpp \
    src/core/config/configplayer.hpp \
    src/core/config/configshortcut.hpp \
    src/core/library.hpp \
    src/core/logger.hpp \
    src/core/player.hpp \
    src/core/tag.hpp \
    src/core/fileutil.hpp \
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
    src/threading/coverloaderworker.hpp \
    src/core/types.hpp \
    src/core/duration.hpp \
    src/core/cover.hpp \
    src/core/playlist.hpp \
    src/core/audios.hpp \
    src/core/filesystemwatcher.hpp \
    src/core/directory.hpp \
    src/core/filesystem.hpp \
    src/core/bimap.hpp \
    src/core/uniquefileinfo.hpp \
    src/core/config/configitem.hpp \
    src/core/shortcut.hpp \
    src/widgets/components/volumebutton.hpp \
    src/widgets/components/playpausebutton.hpp \
    src/threading/base/thread.hpp \
    src/threading/base/threadedobject.hpp \
    src/threading/base/threadpool.hpp \
    src/threading/base/runnable.hpp \
    src/threading/base/callable.hpp \
    src/threading/base/controller.hpp \
    src/threading/initialloaderworker.hpp \
    src/threading/initialloader.hpp \
    src/threading/coverloader.hpp \
    src/threading/audioupdater.hpp \
    src/threading/audioloader.hpp \
    src/threading/base/expiringthread.hpp \
    src/core/utils.hpp

SOURCES += \
    src/main.cpp \
    src/core/audio.cpp \
    src/core/bass/bass.cpp \
    src/core/bass/basserror.cpp \
    src/core/bass/bassstream.cpp \
    src/core/cache.cpp \
    src/core/constants.cpp \
    src/core/config/config.cpp \
    src/core/config/configapp.cpp \
    src/core/config/configbar.cpp \
    src/core/config/configlibrary.cpp \
    src/core/config/configplayer.cpp \
    src/core/config/configshortcut.cpp \
    src/core/library.cpp \
    src/core/logger.cpp \
    src/core/player.cpp \
    src/core/tag.cpp \
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
    src/threading/coverloaderworker.cpp \
    src/core/duration.cpp \
    src/core/cover.cpp \
    src/core/fileutil.cpp \
    src/core/playlist.cpp \
    src/core/audios.cpp \
    src/core/filesystemwatcher.cpp \
    src/core/directory.cpp \
    src/core/filesystem.cpp \
    src/core/uniquefileinfo.cpp \
    src/core/config/configitem.cpp \
    src/core/shortcut.cpp \
    src/widgets/components/volumebutton.cpp \
    src/widgets/components/playpausebutton.cpp \
    src/threading/base/thread.cpp \
    src/threading/base/threadedobject.cpp \
    src/threading/base/threadpool.cpp \
    src/threading/base/runnable.cpp \
    src/threading/base/callable.cpp \
    src/threading/base/controller.cpp \
    src/threading/initialloaderworker.cpp \
    src/threading/initialloader.cpp \
    src/threading/coverloader.cpp \
    src/threading/audioupdater.cpp \
    src/threading/audioloader.cpp \
    src/threading/base/expiringthread.cpp
