#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "cache.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "eggwidget.hpp"
#include "library.hpp"
#include "player.hpp"

QFont font(double size)
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(size);
    font.setWeight(QFont::Weight::Medium);

    return font;
}

void setup(QApplication &app)
{
    qsrand(time(0));

    app.setApplicationName(APP_NAME);
    app.setOrganizationName(APP_ORG_NAME);
    app.setFont(font(cfgApp->fontSize()));

    eLibrary->setSorted(true);

    ePlayer->setVolume(cfgPlayer->volume());
    ePlayer->playlist()->setLoop(cfgPlayer->loop());
    ePlayer->playlist()->setShuffle(cfgPlayer->shuffle());

    Cache().createTables();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setup(app);

    EggWidget egg;
    egg.show();//showSavedPosition();

    return app.exec();
}
