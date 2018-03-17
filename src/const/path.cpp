#include "path.hpp"

QString prefix()
{
#ifdef QT_DEBUG
    return QString();
#else
    return QString(":/");
#endif
}

// Images
const QString IMG_BACK    = prefix() + "images/back.png";
const QString IMG_FORWARD = prefix() + "images/forward.png";
const QString IMG_MUTE    = prefix() + "images/mute.png";
const QString IMG_NEXT    = prefix() + "images/next.png";
const QString IMG_PAUSE   = prefix() + "images/pause.png";
const QString IMG_PLAY    = prefix() + "images/play.png";
const QString IMG_REPLAY  = prefix() + "images/replay.png";
const QString IMG_REWIND  = prefix() + "images/rewind.png";
const QString IMG_SHUFFLE = prefix() + "images/shuffle.png";
const QString IMG_STOP    = prefix() + "images/stop.png";
const QString IMG_VOLUME  = prefix() + "images/volume.png";

// CSS
const QString CSS_ICONBUTTON = prefix() + "css/iconbutton.css";
