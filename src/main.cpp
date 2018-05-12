#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "config.hpp"
#include "constants.hpp"
#include "eggplayer.hpp"
#include "utils.hpp"

/*
 * Checks if all resources are available.
 */
void checkResources()
{
    QStringList resources =
    {
        FONT_LATO,
        ICO_LOOP,
        ICO_NEXT,
        ICO_PAUSE,
        ICO_PLAY,
        ICO_PREVIOUS,
        ICO_SHUFFLE,
        ICO_VOLUME_FULL,
        ICO_VOLUME_LOW,
        ICO_VOLUME_MEDIUM,
        ICO_VOLUME_MUTE,
        IMG_DEFAULT_COVER,
        IMG_EGGPLAYER
    };

    for (const QString &resource : resources)
        if (!Utils::exists(resource))
            Logger::log("Resource does not exist '%1'", {resource});
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
    font.setPointSizeF(Config::App::fontSize());
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

    qApp->setApplicationName(APP_NAME);
    qApp->setOrganizationName(APP_ORG_NAME);
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
