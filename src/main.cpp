#include <QApplication>

#include "src/constants/path.hpp"
#include "src/gui/components/iconbutton.hpp"
#include "src/utils/fileutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(QSize(120, 120));
    window.setStyleSheet("QWidget {background-color: gray}");

    IconButton button(&window);
    button.setStyleSheet(FileUtil::read(CSS_ICONBUTTON));
    button.init(IMG_PLAY, IMG_PAUSE, QSize(100, 100));
    button.setGeometry(10, 10, 100, 100);
    button.show();

    window.show();

    return app.exec();
}
