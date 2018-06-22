#include "constants.hpp"

QString ConstantsPrivate::documents(const QString &file)
{
    QString documents = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString egg = documents + "/egg-player/";
    QDir().mkpath(egg);

    return egg + file;
}

QString ConstantsPrivate::resource(const QString &file)
{
#ifdef QT_DEBUG
    return "resource/" + file;
#else
    return ":/resource/" + file;
#endif
}

const QString CSS_BAR           = ConstantsPrivate::resource("css/bar.css");
const QString CSS_EGG           = ConstantsPrivate::resource("css/egg.css");
const QString CSS_LIBRARY       = ConstantsPrivate::resource("css/library.css");

const QString FONT_LATO         = ConstantsPrivate::resource("fonts/Lato.ttf");

const QString ICO_LOOP          = ConstantsPrivate::resource("images/icons/loop.png");
const QString ICO_NEXT          = ConstantsPrivate::resource("images/icons/next.png");
const QString ICO_PAUSE         = ConstantsPrivate::resource("images/icons/pause.png");
const QString ICO_PLAY          = ConstantsPrivate::resource("images/icons/play.png");
const QString ICO_PREVIOUS      = ConstantsPrivate::resource("images/icons/previous.png");
const QString ICO_SHUFFLE       = ConstantsPrivate::resource("images/icons/shuffle.png");
const QString ICO_VOLUME_FULL   = ConstantsPrivate::resource("images/icons/volume-full.png");
const QString ICO_VOLUME_LOW    = ConstantsPrivate::resource("images/icons/volume-low.png");
const QString ICO_VOLUME_MEDIUM = ConstantsPrivate::resource("images/icons/volume-medium.png");
const QString ICO_VOLUME_MUTE   = ConstantsPrivate::resource("images/icons/volume-mute.png");

const QString IMG_DEFAULT_COVER = ConstantsPrivate::resource("images/default-cover.png");
const QString IMG_EGGPLAYER     = ConstantsPrivate::resource("images/egg/egg.png");

const QString APP_NAME          = "Egg Player";
const QString APP_ORG_NAME      = "Egg Inc.";

const QString SQL_CONNECTION    = "cache";
const QString SQL_PATH          = ConstantsPrivate::documents("cache.db");

const QString CFG_PATH          = ConstantsPrivate::documents("config.json");

const QString LOG_PATH          = ConstantsPrivate::documents("egg.log");
