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
    src/core/audios/currentstate.hpp \
    src/core/bass/basserror.hpp \
    src/core/bass/streamwrapper.hpp \
    src/core/bass/syncwrapper.hpp \
    src/core/config/appjson.hpp \
    src/core/config/barjson.hpp \
    src/core/config/jsonobject.hpp \
    src/core/config/libraryjson.hpp \
    src/core/config/playerjson.hpp \
    src/core/config/shortcutjson.hpp \
    src/core/database/audioitem.hpp \
    src/core/database/coveritem.hpp \
    src/core/database/dbinitializer.hpp \
    src/core/database/infoitem.hpp \
    src/core/database/queryobject.hpp \
    src/core/database/sqlquery.hpp \
    src/core/database/tableitem.hpp \
    src/core/filesystem/filesystemwatcher.hpp \
    src/core/filesystem/uniquefileinfo.hpp \
    src/core/filesystem/windowsfile.hpp \
    src/core/audio.hpp \
    src/core/audios.hpp \
    src/core/bass.hpp \
    src/core/bimap.hpp \
    src/core/cache.hpp \
    src/core/config.hpp \
    src/core/constants.hpp \
    src/core/cover.hpp \
    src/core/duration.hpp \
    src/core/iconcreator.hpp \
    src/core/library.hpp \
    src/core/logger.hpp \
    src/core/macros.hpp \
    src/core/player.hpp \
    src/core/playlist.hpp \
    src/core/shortcut.hpp \
    src/core/shortcutprocessor.hpp \
    src/core/singleton.hpp \
    src/core/tag.hpp \
    src/core/types.hpp \
    src/core/uncopyable.hpp \
    src/core/utils.hpp \
    src/threading/audioloader.hpp \
    src/threading/audioloaderworker.hpp \
    src/threading/audioupdater.hpp \
    src/threading/callable.hpp \
    src/threading/controller.hpp \
    src/threading/coverloader.hpp \
    src/threading/coverloaderworker.hpp \
    src/threading/expiringthread.hpp \
    src/threading/runnable.hpp \
    src/threading/thread.hpp \
    src/threading/threadobject.hpp \
    src/threading/threadpool.hpp \
    src/widgets/audioswidget.hpp \
    src/widgets/barwidget.hpp \
    src/widgets/borderlayout.hpp \
    src/widgets/clickablestyle.hpp \
    src/widgets/eggwidget.hpp \
    src/widgets/iconbutton.hpp \
    src/widgets/librarywidget.hpp \
    src/widgets/lockableiconbutton.hpp \
    src/widgets/mainwindow.hpp \
    src/widgets/playpausebutton.hpp \
    src/widgets/rowhoverdelegate.hpp \
    src/widgets/slider.hpp \
    src/widgets/smoothtablewidget.hpp \
    src/widgets/tablewidget.hpp \
    src/widgets/volumebutton.hpp \
    src/core/filesystem/directory.hpp \
    src/core/filesystem.hpp \
    src/core/readablevector.hpp \
    src/core/audios/audiosbase.hpp

SOURCES += \
    src/core/audios/currentstate.cpp \
    src/core/bass/basserror.cpp \
    src/core/bass/streamwrapper.cpp \
    src/core/bass/syncwrapper.cpp \
    src/core/config/appjson.cpp \
    src/core/config/barjson.cpp \
    src/core/config/jsonobject.cpp \
    src/core/config/libraryjson.cpp \
    src/core/config/playerjson.cpp \
    src/core/config/shortcutjson.cpp \
    src/core/database/audioitem.cpp \
    src/core/database/coveritem.cpp \
    src/core/database/dbinitializer.cpp \
    src/core/database/infoitem.cpp \
    src/core/database/queryobject.cpp \
    src/core/database/sqlquery.cpp \
    src/core/filesystem/filesystemwatcher.cpp \
    src/core/filesystem/uniquefileinfo.cpp \
    src/core/filesystem/windowsfile.cpp \
    src/core/audio.cpp \
    src/core/audios.cpp \
    src/core/bass.cpp \
    src/core/cache.cpp \
    src/core/config.cpp \
    src/core/constants.cpp \
    src/core/cover.cpp \
    src/core/duration.cpp \
    src/core/iconcreator.cpp \
    src/core/library.cpp \
    src/core/logger.cpp \
    src/core/player.cpp \
    src/core/playlist.cpp \
    src/core/shortcut.cpp \
    src/core/shortcutprocessor.cpp \
    src/core/tag.cpp \
    src/core/utils.cpp \
    src/threading/audioloader.cpp \
    src/threading/audioloaderworker.cpp \
    src/threading/audioupdater.cpp \
    src/threading/callable.cpp \
    src/threading/controller.cpp \
    src/threading/coverloader.cpp \
    src/threading/coverloaderworker.cpp \
    src/threading/expiringthread.cpp \
    src/threading/runnable.cpp \
    src/threading/thread.cpp \
    src/threading/threadobject.cpp \
    src/threading/threadpool.cpp \
    src/widgets/audioswidget.cpp \
    src/widgets/barwidget.cpp \
    src/widgets/borderlayout.cpp \
    src/widgets/clickablestyle.cpp \
    src/widgets/eggwidget.cpp \
    src/widgets/iconbutton.cpp \
    src/widgets/librarywidget.cpp \
    src/widgets/lockableiconbutton.cpp \
    src/widgets/mainwindow.cpp \
    src/widgets/playpausebutton.cpp \
    src/widgets/rowhoverdelegate.cpp \
    src/widgets/slider.cpp \
    src/widgets/smoothtablewidget.cpp \
    src/widgets/tablewidget.cpp \
    src/widgets/volumebutton.cpp \
    src/main.cpp \
    src/core/filesystem/directory.cpp \
    src/core/filesystem.cpp \
    src/core/audios/audiosbase.cpp
