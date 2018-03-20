#include <QApplication>
#include <QMediaPlayer>

#include "src/core/library.hpp"
#include "src/core/audiofile.hpp"
#include "src/utils/fileutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(200, 200);

    Library lib("C:/Users/Julian/Music");
    lib.sortByTitle();

    for (AudioFile audioFile : lib.library())
        qDebug().noquote() << audioFile.title() << "-" << audioFile.artist();

    window.show();
    return app.exec();
}
