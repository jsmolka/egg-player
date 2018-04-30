#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include <QStringList>

#include "config.hpp"
#include "constants.hpp"
#include "eggplayer.hpp"
#include "logger.hpp"
#include "shortcut.hpp"
#include "utils.hpp"

/*
 * Checks if all needed resources are available.
 */
void checkResources()
{
    QStringList resources =
    {
        CSS_MUSICBAR, CSS_MUSICLIBRARY, FONT_LATO, ICO_PREVIOUS, ICO_EXPAND, ICO_FASTFORWARD,
        ICO_FASTREWIND, ICO_FORWARD, ICO_HEART, ICO_MINIMIZE, ICO_MUTE, ICO_NEXT, ICO_PAUSE,
        ICO_PLAY, ICO_REPLAY, ICO_REWIND, ICO_SHUFFLE, ICO_STOP, ICO_VOLUME, ICO_VOLUME1,
        ICO_VOLUME2, IMG_DEFAULT_COVER, IMG_EGGPLAYER
    };

    for (QString resource : resources)
        if (!Utils::exists(resource))
            Logger::log("Resource not found '%1'", resource);
}

/*
 * Loads custom font.
 *
 * :return: font
 */
QFont loadFont()
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(Config::AFontSize());
    font.setWeight(QFont::Weight::Medium);

    return font;
}

/*
 * Sets up application.
 */
void setup()
{
    Config::create();
    Logger::create();

    checkResources();

    qApp->setApplicationName(LANG_APP_NAME);
    qApp->setOrganizationName(LANG_ORG_NAME);
    qApp->setFont(loadFont());
}

/*
 * Main function.
 *
 * :param argc: argc
 * :param argv: argv
 * :return: exit code
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setup();

    EggPlayer player;
    player.showSavedPosition();

    return app.exec();
}
