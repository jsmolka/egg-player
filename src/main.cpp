#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QStringList>
#include <QPixmap>

#include <iostream>

#include "src/core/audiofile.hpp"
#include "src/utils/fileutil.hpp"
#include "src/utils/randutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(500, 500);

    QList<AudioFile> audioList;
    QString path = "C:/Users/Julian/Music";
    for (QString string : FileUtil::glob(path, "*.mp3"))
    {
        AudioFile audio(string, false);
        audioList.append(audio);
    }

    QLabel label(&window);
    label.setFixedSize(500, 500);

    QPixmap pix;
    qint32 rand = RandUtil::randint(audioList.size());
    AudioFile file = audioList.at(rand);
    QImage image = file.getCover();
    image = image.scaled(500, 500, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pix.convertFromImage(image);
    label.setPixmap(pix);

    label.show();
    window.show();
    return app.exec();
}
