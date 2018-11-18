#include "constants.hpp"

#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

#include "core/logger.hpp"

QString resource(const QString &file)
{
#ifdef QT_DEBUG
    return "resource/" + file;
#else
    return ":/resource/" + file;
#endif
}

QString document(const QString &file)
{
    const QString documents = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    const QString egg = documents + "/egg-player/";
    QDir().mkpath(egg);

    return egg + file;
}

namespace constants
{

namespace css
{
const QString Bar = resource("css/bar.css");
const QString Egg = resource("css/egg.css");
const QString Library = resource("css/library.css");
}

namespace font
{
const QString Lato = resource("fonts/Lato.ttf");
}

namespace ico
{
const QString Loop = resource("images/icons/loop.png");
const QString Next = resource("images/icons/next.png");
const QString Pause = resource("images/icons/pause.png");
const QString Play = resource("images/icons/play.png");
const QString Previous = resource("images/icons/previous.png");
const QString Shuffle = resource("images/icons/shuffle.png");

namespace volume
{
const QString Full = resource("images/icons/volume-full.png");
const QString Low = resource("images/icons/volume-low.png");
const QString Medium = resource("images/icons/volume-medium.png");
const QString Mute = resource("images/icons/volume-mute.png");
}

}

namespace img
{
const QString Cover = resource("images/default-cover.png");
const QString Egg = resource("images/egg/egg.png");
}

namespace app
{
const QString Name = "Egg Player";
const QString Org  = "Egg Inc.";
}

namespace db
{
const QString Connection = "cache";
const QString File = document("cache.db");
}

namespace cfg
{
const QString File = document("config.json");
}

namespace log
{
const QString File = document("egg.log");
}

}
