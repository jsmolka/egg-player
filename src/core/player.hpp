#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QList>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <src/core/audiofile.hpp>

class Player : public QMediaPlayer
{
public:
    explicit Player(QObject *parent = 0);

    void setAudioList(QList<AudioFile> audioList);
    QList<AudioFile> audioList() const;

    bool refresh();

private:
    QMediaPlaylist *m_playlist;
    QList<AudioFile> m_audioList;
};

#endif // PLAYER_HPP
