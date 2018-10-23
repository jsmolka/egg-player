#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "config.hpp"
#include "constants.hpp"
#include "dbinitializer.hpp"
#include "eggwidget.hpp"
#include "library.hpp"
#include "player.hpp"
#include "types.hpp"

QFont font(double size)
{
    const int id = QFontDatabase::addApplicationFont(FONT_LATO);
    const QString family = QFontDatabase::applicationFontFamilies(id).at(0);

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
    app.setFont(font(cfgApp.fontSize()));

    ePlayer->setVolume(cfgPlayer.volume());
    ePlayer->playlist().setLoop(cfgPlayer.loop());
    ePlayer->playlist().setShuffle(cfgPlayer.shuffle());

    DbInitializer().initialize();

    qRegisterMetaType<File>("File");
    qRegisterMetaType<Path>("Path");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setup(app);

    EggWidget egg;
    egg.showSavedState();

    return app.exec();
}
