#include "constants.hpp"

/*
 * Returns the documents path for a give file. Creates the egg players documents
 * directory if it does not exist already.
 *
 * :param file: file
 * :return: documents path
 */
QString documents(const QString &file)
{
    QString documents = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString egg = documents + "/egg-player/";
    QDir().mkpath(egg);

    return egg + file;
}

/*
 * Returns the resource location depending on debug or release mode. In debug
 * mode the files will be read from the disk to make finetuning easier. In
 * release mode the Qt resource system will be used to remove the need to
 * include the resource folder.
 *
 * :param file: file
 * :return: resource file
 */
QString resource(const QString &file)
{
#ifdef QT_DEBUG
    return "resource/" + file;
#else
    return ":/resource/" + file;
#endif
}

const QString CSS_MUSICBAR      = resource("css/musicbar.css");
const QString CSS_MUSICLIBRARY  = resource("css/musiclibrary.css");

const QString FONT_LATO         = resource("fonts/Lato.ttf");

const QString ICO_LOOP          = resource("images/icons/loop.png");
const QString ICO_NEXT          = resource("images/icons/next.png");
const QString ICO_PAUSE         = resource("images/icons/pause.png");
const QString ICO_PLAY          = resource("images/icons/play.png");
const QString ICO_PREVIOUS      = resource("images/icons/previous.png");
const QString ICO_SHUFFLE       = resource("images/icons/shuffle.png");
const QString ICO_VOLUME_FULL   = resource("images/icons/volume-full.png");
const QString ICO_VOLUME_LOW    = resource("images/icons/volume-low.png");
const QString ICO_VOLUME_MEDIUM = resource("images/icons/volume-medium.png");
const QString ICO_VOLUME_MUTE   = resource("images/icons/volume-mute.png");

const QString IMG_DEFAULT_COVER = resource("images/default-cover.png");
const QString IMG_EGGPLAYER     = resource("images/egg/egg.png");

const QString APP_NAME          = "Egg Player";
const QString APP_ORG_NAME      = "Egg Inc.";

const QString SQL_CONNECTION    = "cache";
const QString SQL_PATH          = documents("cache.db");

const QString CFG_PATH          = documents("config.json");

const QString LOG_PATH          = documents("egg.log");
