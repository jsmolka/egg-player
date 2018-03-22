#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <src/core/audio.hpp>
#include <src/core/audiolist.hpp>

class Player : public QMediaPlayer
{
public:
    explicit Player(QObject *parent = 0);

    void setAudioList(AudioList audioList);
    AudioList audioList() const;

    bool refresh();

private:
    QMediaPlaylist *m_playlist;
    AudioList m_audioList;
};

#endif // PLAYER_HPP
