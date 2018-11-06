#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "core/constants.hpp"
#include "core/player.hpp"
#include "core/database/dbinitializer.hpp"
#include "widgets/eggwidget.hpp"

QFont font()
{
    const int id = QFontDatabase::addApplicationFont(constants::font::lato);
    const QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(cfg_app.fontSize());
    font.setWeight(QFont::Weight::Medium);

    return font;
}

void setup(QApplication &app)
{
    qsrand(time(0));

    app.setApplicationName(constants::app::name);
    app.setOrganizationName(constants::app::org);
    app.setFont(font());

    egg_player.setVolume(cfg_player.volume());
    egg_player.playlist().setLoop(cfg_player.loop());
    egg_player.playlist().setShuffle(cfg_player.shuffle());

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
