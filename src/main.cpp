#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "config.hpp"
#include "constants.hpp"
#include "eggplayer.hpp"
#include "logger.hpp"

QFont loadFont()
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(Config::fontSize());
    font.setWeight(QFont::Weight::Medium);

    return font;
}

void setup(QApplication *app)
{
    Config::create();
    Logger::create();

    app->setApplicationName(LANG_APP_NAME);
    app->setOrganizationName(LANG_ORG_NAME);
    app->setFont(loadFont());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setup(&app);

    EggPlayer player;
    player.showSavedPosition();

    return app.exec();
}
