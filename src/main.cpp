#include <QApplication>

#include "config.hpp"
#include "constants.hpp"
#include "eggwidget.hpp"
#include "library.hpp"
#include "player.hpp"

void setup()
{
    qsrand(time(0));

    qApp->setApplicationName(APP_NAME);
    qApp->setOrganizationName(APP_ORG_NAME);
    qApp->setFont(Util::font(cfgApp->fontSize()));

    eLibrary->setSorted(true);

    ePlayer->setVolume(cfgPlayer->volume());
    ePlayer->setShuffle(cfgPlayer->shuffle());
    ePlayer->setLoop(cfgPlayer->loop());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setup();

    EggWidget egg;
    egg.showSavedPosition();

    return app.exec();
}
