#include <QApplication>

#include "constants.hpp"
#include "eggplayer.hpp"
#include "utils.hpp"

/*
 * Sets up application.
 */
void setup()
{
    Config::create();
    Logger::create();

    Utils::checkResources();

    qApp->setApplicationName(APP_NAME);
    qApp->setOrganizationName(APP_ORG_NAME);
    qApp->setFont(Utils::loadFont());
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
