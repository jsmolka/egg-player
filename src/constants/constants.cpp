#include "constants.hpp"

/*
 * This function returns the egg players documents
 * directory and creates it if it does not exist
 * already.
 *
 * :return: directory
 */
QString documents()
{
    QString directory = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/egg-player";
    QDir().mkpath(directory);

    return directory;
}

const QString DOCUMENTS        = documents();

const QString CSS_MUSICBAR     = "resource/css/musicbar.css";
const QString CSS_MUSICLIBRARY = "resource/css/musiclibrary.css";

const QString FONT_LATO         = "resource/fonts/Lato.ttf";

const QString ICO_LOOP          = "resource/images/icons/loop.png";
const QString ICO_NEXT          = "resource/images/icons/next.png";
const QString ICO_PAUSE         = "resource/images/icons/pause.png";
const QString ICO_PLAY          = "resource/images/icons/play.png";
const QString ICO_PREVIOUS      = "resource/images/icons/previous.png";
const QString ICO_SHUFFLE       = "resource/images/icons/shuffle.png";
const QString ICO_VOLUME_FULL   = "resource/images/icons/volume-full.png";
const QString ICO_VOLUME_LOW    = "resource/images/icons/volume-low.png";
const QString ICO_VOLUME_MEDIUM = "resource/images/icons/volume-medium.png";
const QString ICO_VOLUME_MUTE   = "resource/images/icons/volume-mute.png";

const QString IMG_DEFAULT_COVER = "resource/images/default-cover.png";
const QString IMG_EGGPLAYER     = "resource/images/egg/egg.png";

const QString APP_NAME          = "Egg Player";
const QString APP_ORG_NAME      = "Egg Inc.";

const QString SQL_CONNECTION    = "cache";
const QString SQL_PATH          = DOCUMENTS + "/cache.db";

const QString CFG_PATH          = DOCUMENTS + "/config.json";

const QString LOG_PATH          = DOCUMENTS + "/egg.log";
