#include "constants.hpp"

QString documents()
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/egg-player";
    QDir().mkdir(directory);
    return directory;
}

const QString DOCUMENTS        = documents();

const QString CSS_MUSICBAR     = FileUtil::read("resource/css/musicbar.css");
const QString CSS_MUSICLIBRARY = FileUtil::read("resource/css/musiclibrary.css");

const QString FONT_LATO         = "resource/fonts/Lato.ttf";
const QString ICO_BACK          = "resource/images/icons/back.png";
const QString ICO_EXPAND        = "resource/images/icons/expand.png";
const QString ICO_FASTFORWARD   = "resource/images/icons/fastforward.png";
const QString ICO_FASTREWIND    = "resource/images/icons/fastrewind.png";
const QString ICO_FORWARD       = "resource/images/icons/forward.png";
const QString ICO_HEART         = "resource/images/icons/heart.png";
const QString ICO_MINIMIZE      = "resource/images/icons/minimize.png";
const QString ICO_MUTE          = "resource/images/icons/mute.png";
const QString ICO_NEXT          = "resource/images/icons/next.png";
const QString ICO_PAUSE         = "resource/images/icons/pause.png";
const QString ICO_PLAY          = "resource/images/icons/play.png";
const QString ICO_REPLAY        = "resource/images/icons/replay.png";
const QString ICO_REWIND        = "resource/images/icons/rewind.png";
const QString ICO_SHUFFLE       = "resource/images/icons/shuffle.png";
const QString ICO_STOP          = "resource/images/icons/stop.png";
const QString ICO_VOLUME        = "resource/images/icons/volume.png";
const QString ICO_VOLUME1       = "resource/images/icons/volume1.png";
const QString ICO_VOLUME2       = "resource/images/icons/volume2.png";
const QString IMG_DEFAULT_COVER = "resource/images/default-cover.png";

const QString LANG_APP_NAME     = "Egg Player";
const QString LANG_ORG_NAME     = "Egg Inc.";

const QString SQL_CONNECTION    = "cache";
const QString SQL_PATH          = DOCUMENTS + "/cache.db";

const QString CFG_PATH          = DOCUMENTS + "/config.ini";
