#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "config.hpp"
#include "constants.hpp"
#include "eggwidget.hpp"
#include "logger.hpp"

QFont loadFont()
{
    int id = QFontDatabase::addApplicationFont(FONT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(cfgApp->fontSize());
    font.setWeight(QFont::Weight::Medium);

    return font;
}

void setup()
{
    qApp->setApplicationName(APP_NAME);
    qApp->setOrganizationName(APP_ORG_NAME);
    qApp->setFont(loadFont());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    log("Application: Start");

    setup();

    EggWidget egg;
    egg.showSavedPosition();

    return app.exec();
}
