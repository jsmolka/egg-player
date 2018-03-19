#include <QApplication>
#include <QDebug>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QList>
#include <QStringList>

#include "src/core/audiofile.hpp"
#include "src/utils/fileutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    AudioFile file("Soulmate.mp3");

    qDebug() << "valid: " << file.isValid();
    qDebug() << "title: " << file.title();
    qDebug() << "artist: " << file.artist();
    qDebug() << "album: " << file.album();
    qDebug() << "year: " << file.year();
    qDebug() << "track: " << file.track();
    qDebug() << "genre: " << file.genre();
    qDebug() << "length: " << file.length();
    qDebug() << "bitrate: " << file.bitrate();
    qDebug() << "seconds: " << file.seconds();
    qDebug() << "minutes: " << file.minutes();

    QWidget window;
    window.setFixedSize(500, 500);

    QLabel label(&window);
    label.setPixmap(QPixmap::fromImage(file.cover().scaledToWidth(500)));
    label.show();

    window.show();
    QList<AudioFile> fileList;
    QString path("C:/Users/Julian/Music");
    QStringList stringList = FileUtil::glob(path, "*.mp3");
    for (QString string : stringList)
    {
        fileList.append(AudioFile(string, false));
        qDebug() << string;
    }

    return app.exec();
}
