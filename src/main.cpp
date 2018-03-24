#include <QApplication>
#include <QFont>
#include <QFontDatabase>

#include "src/constants/path.hpp"
#include "src/ui/mainwindow.hpp"

QFont loadFont()
{
    int id = QFontDatabase::addApplicationFont(FNT_LATO);
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(family);
    font.setPointSizeF(10.25);
    font.setWeight(QFont::Weight::Medium);

    return font;
}

void setup(QApplication *app)
{
    app->setFont(loadFont());
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setup(&app);

    MainWindow window;
    window.showMaximized();

    return app.exec();
}
