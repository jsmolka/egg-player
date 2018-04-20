#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include <QStringList>

#include "config.hpp"
#include "constants.hpp"
#include "eggplayer.hpp"
#include "fileutil.hpp"
#include "logger.hpp"

/*
 * Checks if all needed resources are available.
 */
void checkResources()
{
    QStringList resources =
    {
        CSS_MUSICBAR, CSS_MUSICLIBRARY, FONT_LATO, ICO_BACK, ICO_EXPAND, ICO_FASTFORWARD,
        ICO_FASTREWIND, ICO_FORWARD, ICO_HEART, ICO_MINIMIZE, ICO_MUTE, ICO_NEXT, ICO_PAUSE,
        ICO_PLAY, ICO_REPLAY, ICO_REWIND, ICO_SHUFFLE, ICO_STOP, ICO_VOLUME, ICO_VOLUME1,
        ICO_VOLUME2, IMG_DEFAULT_COVER, IMG_EGGPLAYER
    };

    for (QString resource : resources)
        if (!FileUtil::exists(resource))
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
    font.setPointSizeF(Config::fontSize());
    font.setWeight(QFont::Weight::Medium);

    return font;
}

/*
 * Sets up application.
 *
 * :param app: application pointer
 */
void setup(QApplication *app)
{
    Config::create();
    Logger::create();

    checkResources();

    app->setApplicationName(LANG_APP_NAME);
    app->setOrganizationName(LANG_ORG_NAME);
    app->setFont(loadFont());
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

    setup(&app);

    EggPlayer player;
    player.showSavedPosition();

    return app.exec();
}
