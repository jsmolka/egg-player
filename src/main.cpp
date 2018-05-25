#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "config.hpp"
#include "constants.hpp"
#include "eggplayer.hpp"
#include "logger.hpp"

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

    Logger::log("Application: Start");

    setup();

    EggPlayer egg;
    egg.showSavedPosition();

    return app.exec();
}
