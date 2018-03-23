#include <QApplication>

#include "src/gui/mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.showMaximized();

    return app.exec();
}
