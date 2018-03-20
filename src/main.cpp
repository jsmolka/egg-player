#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QStringList>
#include <QPixmap>
#include <QMediaPlayer>

#include <iostream>

#include "src/core/audiofile.hpp"
#include "src/utils/fileutil.hpp"
#include "src/utils/randutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QLabel label(&window);

    window.setFixedSize(500, 500);
    label.setFixedSize(500, 500);

    QList<AudioFile> audioList;
    for (QString string : FileUtil::glob("C:/Users/Julian/Music/Sum 41/Underclass Hero", "*.mp3"))
        audioList.append(AudioFile(string));

    AudioFile audioFile = audioList.at(RandUtil::randint(audioList.size()));
    QImage image = audioFile.getCover();
    QPixmap pixmap;
    pixmap.convertFromImage(image.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label.setPixmap(pixmap);

    qDebug() << "read audio files:" << audioList.size();
    qDebug() << "playing:" << audioFile.title();

    QMediaPlayer *player = new QMediaPlayer();
    player->setMedia(audioFile.url());
    player->setVolume(20);
    player->play();

    label.show();
    window.show();
    return app.exec();
}
