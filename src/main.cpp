#include <QDebug>
#include <QList>
#include <QStringList>

#include "src/core/audiofile.hpp"
#include "src/utils/fileutil.hpp"

int main(int argc, char *argv[])
{
    QList<AudioFile> audioList;
    QString path("C:/Users/Julian/Music");
    for (QString string : FileUtil::glob(path, "*.mp3"))
    {
        AudioFile audio(string, false);
        qDebug() << audio.path();
        audioList.append(audio);
    }
    return 0;
}
