#include <QDebug>

#include "src/core/audiofile.hpp"

int main(int argc, char *argv[])
{
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

    return 0;
}
