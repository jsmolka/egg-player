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
    src/threading/audioloaderworker.hpp \
    src/threading/coverloaderworker.hpp \
    src/core/types.hpp \
    src/threading/abstractworker.hpp \
    src/threading/abstractcontroller.hpp \
    src/threading/coverloadercontroller.hpp \
    src/threading/audioloadercontroller.hpp \
    src/core/duration.hpp \
    src/core/cover.hpp \
    src/core/playlist.hpp \
    src/core/audios.hpp \
    src/threading/audioupdatercontroller.hpp \
    src/threading/audioupdaterworker.hpp \
    src/core/filesystemwatcher.hpp \
    src/core/directory.hpp

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
    src/threading/audioloaderworker.cpp \
    src/threading/coverloaderworker.cpp \
    src/threading/abstractworker.cpp \
    src/threading/abstractcontroller.cpp \
    src/threading/coverloadercontroller.cpp \
    src/threading/audioloadercontroller.cpp \
    src/core/duration.cpp \
    src/core/cover.cpp \
    src/core/fileutil.cpp \
    src/core/playlist.cpp \
    src/core/audios.cpp \
    src/threading/audioupdatercontroller.cpp \
    src/threading/audioupdaterworker.cpp \
    src/core/filesystemwatcher.cpp \
    src/core/directory.cpp

