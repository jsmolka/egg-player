TARGET = egg-player
TEMPLATE = app

RC_ICONS += \
    data/images/egg/egg.ico

QT += \
    core \
    widgets \
    multimedia \
    sql

INCLUDEPATH += \
    ext/taglib/include

LIBS += \
    -L"$$PWD/ext/taglib/lib" -ltag.dll

HEADERS += \
    src/core/audio.hpp \
    src/core/audiolist.hpp \
    src/core/library.hpp \
    src/core/player.hpp \
    src/ui/components/iconbutton.hpp \
    src/ui/components/songinfo.hpp \
    src/ui/layouts/borderlayout.hpp \
    src/utils/fileutil.hpp \
    src/constants/constant.hpp \
    src/ui/eggplayer.hpp \
    src/ui/musicbar.hpp \
    src/ui/musiclibrary.hpp \
    src/constants/language.hpp \
    src/core/cache.hpp \
    src/utils/colorutil.hpp

SOURCES += \
    src/main.cpp \
    src/core/audio.cpp \
    src/core/audiolist.cpp \
    src/core/library.cpp \
    src/core/player.cpp \
    src/ui/components/iconbutton.cpp \
    src/ui/components/songinfo.cpp \
    src/ui/layouts/borderlayout.cpp \
    src/utils/fileutil.cpp \
    src/constants/constant.cpp \
    src/ui/eggplayer.cpp \
    src/ui/musicbar.cpp \
    src/ui/musiclibrary.cpp \
    src/constants/language.cpp \
    src/core/cache.cpp \
    src/utils/colorutil.cpp
