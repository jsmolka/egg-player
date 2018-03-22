#include <QApplication>
#include <QWidget>

#include "src/core/audio.hpp"
#include "src/core/audiolist.hpp"
#include "src/core/library.hpp"
#include "src/core/player.hpp"
#include "src/utils/fileutil.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(500, 500);

    Library lib("C:/Users/Julian/Music");

    AudioList result = lib.searchByAlbum("swell");
    result.sortByTrack();

    Player player;
    player.setAudioList(result);
    player.shuffle();
    player.setIndex(2);

    for (Audio audio : player.audioList())
        qDebug() << audio.track() << audio.artist() << audio.title();

    player.setVolume(5);
    player.play();

    window.show();
    return app.exec();
}
