#include <QApplication>
#include <QWidget>

#include "src/core/audiofile.hpp"
#include "src/core/library.hpp"
#include "src/core/player.hpp"
#include "src/utils/fileutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(500, 500);

    Library lib("C:/Users/Julian/Music");

    QList<AudioFile> result = lib.searchByAlbum("swell");
    for (AudioFile audio : result)
        qDebug() << audio.track() << audio.title() << audio.artist();

    Player player;
    player.setAudioList(result);
    player.setVolume(5);
    player.play();

    window.show();
    return app.exec();
}
