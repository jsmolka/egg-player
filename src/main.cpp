#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "core/globals.hpp"
#include "core/library.hpp"
#include "core/player.hpp"
#include "core/database/dbinitializer.hpp"
#include "widgets/eggwidget.hpp"

QFont font(double size)
{
    const int id = QFontDatabase::addApplicationFont(constants::font::lato);
    const QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(size);
    font.setWeight(QFont::Weight::Medium);

    return font;
}

void setup(QApplication &app)
{
    qsrand(time(0));

    app.setApplicationName(constants::app::name);
    app.setOrganizationName(constants::app::org);
    app.setFont(font(cfgApp.fontSize()));

    ePlayer->setVolume(cfgPlayer.volume());
    ePlayer->playlist().setLoop(cfgPlayer.loop());
    ePlayer->playlist().setShuffle(cfgPlayer.shuffle());

    db::Initializer::initialize();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    setup(app);

    EggWidget egg;
    egg.showSavedState();

    return app.exec();
}
