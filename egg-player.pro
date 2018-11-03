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
    src

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
    src/core/constants.hpp \
    src/core/config/config.hpp \
    src/core/library.hpp \
    src/core/logger.hpp \
    src/core/player.hpp \
    src/core/tag.hpp \
    src/widgets/eggwidget.hpp \
    src/widgets/barwidget.hpp \
    src/widgets/parts/borderlayout.hpp \
    src/widgets/parts/clickablestyle.hpp \
    src/widgets/parts/iconbutton.hpp \
    src/widgets/parts/iconfactory.hpp \
    src/widgets/parts/mainwindow.hpp \
    src/widgets/parts/rowhoverdelegate.hpp \
    src/widgets/parts/slider.hpp \
    src/widgets/parts/smoothtablewidget.hpp \
    src/widgets/parts/tablewidget.hpp \
    src/threading/coverloaderworker.hpp \
    src/core/duration.hpp \
    src/core/cover.hpp \
    src/core/playlist.hpp \
    src/core/audios.hpp \
    src/core/filesystem/filesystemwatcher.hpp \
    src/core/filesystem/directory.hpp \
    src/core/filesystem/filesystem.hpp \
    src/core/bimap.hpp \
    src/core/filesystem/uniquefileinfo.hpp \
    src/core/shortcut.hpp \
    src/widgets/parts/volumebutton.hpp \
    src/widgets/parts/playpausebutton.hpp \
    src/threading/core/thread.hpp \
    src/threading/core/threadpool.hpp \
    src/threading/core/runnable.hpp \
    src/threading/core/callable.hpp \
    src/threading/core/controller.hpp \
    src/threading/initialloaderworker.hpp \
    src/threading/initialloader.hpp \
    src/threading/coverloader.hpp \
    src/threading/audioupdater.hpp \
    src/threading/audioloader.hpp \
    src/threading/core/expiringthread.hpp \
    src/core/utils.hpp \
    src/core/database/sqlquery.hpp \
    src/widgets/parts/audioswidget.hpp \
    src/widgets/librarywidget.hpp \
    src/core/database/dbtableitem.hpp \
    src/core/database/dbaudio.hpp \
    src/core/database/dbinitializer.hpp \
    src/core/database/dbprovider.hpp \
    src/core/globals.hpp \
    src/core/database/dbbase.hpp \
    src/core/database/dbcover.hpp \
    src/core/database/cache.hpp \
    src/core/types.hpp \
    src/core/macros.hpp \
    src/threading/core/threadobject.hpp \
    src/core/config/cfgapp.hpp \
    src/core/config/cfgbar.hpp \
    src/core/config/cfgbase.hpp \
    src/core/config/cfglibrary.hpp \
    src/core/config/cfgplayer.hpp \
    src/core/config/cfgshortcut.hpp \
    src/widgets/parts/lockableiconbutton.hpp \
    src/core/config/cfgappminimalsize.hpp \
    src/core/config/cfgbarslider.hpp \
    src/core/config/cfgbarlabelwidth.hpp

SOURCES += \
    src/main.cpp \
    src/core/audio.cpp \
    src/core/bass/bass.cpp \
    src/core/bass/basserror.cpp \
    src/core/bass/bassstream.cpp \
    src/core/constants.cpp \
    src/core/config/config.cpp \
    src/core/library.cpp \
    src/core/logger.cpp \
    src/core/player.cpp \
    src/core/tag.cpp \
    src/widgets/eggwidget.cpp \
    src/widgets/barwidget.cpp \
    src/widgets/parts/borderlayout.cpp \
    src/widgets/parts/clickablestyle.cpp \
    src/widgets/parts/iconbutton.cpp \
    src/widgets/parts/iconfactory.cpp \
    src/widgets/parts/mainwindow.cpp \
    src/widgets/parts/rowhoverdelegate.cpp \
    src/widgets/parts/slider.cpp \
    src/widgets/parts/smoothtablewidget.cpp \
    src/widgets/parts/tablewidget.cpp \
    src/threading/coverloaderworker.cpp \
    src/core/duration.cpp \
    src/core/cover.cpp \
    src/core/playlist.cpp \
    src/core/audios.cpp \
    src/core/filesystem/filesystemwatcher.cpp \
    src/core/filesystem/directory.cpp \
    src/core/filesystem/filesystem.cpp \
    src/core/filesystem/uniquefileinfo.cpp \
    src/core/shortcut.cpp \
    src/widgets/parts/volumebutton.cpp \
    src/widgets/parts/playpausebutton.cpp \
    src/threading/core/thread.cpp \
    src/threading/core/threadpool.cpp \
    src/threading/core/runnable.cpp \
    src/threading/core/callable.cpp \
    src/threading/core/controller.cpp \
    src/threading/initialloaderworker.cpp \
    src/threading/initialloader.cpp \
    src/threading/coverloader.cpp \
    src/threading/audioupdater.cpp \
    src/threading/audioloader.cpp \
    src/threading/core/expiringthread.cpp \
    src/core/database/sqlquery.cpp \
    src/widgets/parts/audioswidget.cpp \
    src/widgets/librarywidget.cpp \
    src/core/database/dbaudio.cpp \
    src/core/database/dbinitializer.cpp \
    src/core/database/dbprovider.cpp \
    src/core/database/dbbase.cpp \
    src/core/database/dbcover.cpp \
    src/core/database/cache.cpp \
    src/threading/core/threadobject.cpp \
    src/core/config/cfgapp.cpp \
    src/core/config/cfgbar.cpp \
    src/core/config/cfgbase.cpp \
    src/core/config/cfglibrary.cpp \
    src/core/config/cfgplayer.cpp \
    src/core/config/cfgshortcut.cpp \
    src/widgets/parts/lockableiconbutton.cpp \
    src/core/config/cfgappminimalsize.cpp \
    src/core/config/cfgbarslider.cpp \
    src/core/config/cfgbarlabelwidth.cpp
