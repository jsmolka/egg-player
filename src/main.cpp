#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "src/constants/constant.hpp"
#include "src/constants/language.hpp"
#include "src/ui/eggplayer.hpp"

QFont loadFont()
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    font.setPointSizeF(10.25);
    font.setWeight(QFont::Weight::Medium);

    return font;
}

void setup(QApplication *app)
{
    app->setApplicationName(LANG_APP_NAME);
    app->setFont(loadFont());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setup(&app);

    EggPlayer player;
    player.showMaximized();

    return app.exec();
}
