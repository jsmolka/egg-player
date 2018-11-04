#include "constants.hpp"

#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

#include "core/logger.hpp"

QString checkResource(const QString &file)
{
    if (!QFileInfo::exists(file))
        EGG_LOG("Resource file does not exist %1", file);

    return file;
}

QString resource(const QString &file)
{
#ifdef QT_DEBUG
    return checkResource("resource/" + file);
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
const QString bar = resource("css/bar.css");
const QString egg = resource("css/egg.css");
const QString library = resource("css/library.css");
}

namespace font
{
const QString lato = resource("fonts/Lato.ttf");
}

namespace ico
{
const QString loop = resource("images/icons/loop.png");
const QString next = resource("images/icons/next.png");
const QString pause = resource("images/icons/pause.png");
const QString play = resource("images/icons/play.png");
const QString previous = resource("images/icons/previous.png");
const QString shuffle = resource("images/icons/shuffle.png");

namespace volume
{
const QString full = resource("images/icons/volume-full.png");
const QString low = resource("images/icons/volume-low.png");
const QString medium = resource("images/icons/volume-medium.png");
const QString mute = resource("images/icons/volume-mute.png");
}
}

namespace img
{
const QString cover = resource("images/default-cover.png");
const QString egg = resource("images/egg/egg.png");
}

namespace app
{
const QString name = "Egg Player";
const QString org  = "Egg Inc.";
}

namespace db
{
const QString connection = "cache";
const QString file = document("cache.db");
}

namespace cfg
{
const QString file = document("config.json");
}

namespace log
{
const QString file = document("egg.log");
}
}
