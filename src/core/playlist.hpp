#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <QObject>
#include <QVector>

#include "audio.hpp"
#include "audios.hpp"

class Playlist : public QObject
{
    Q_OBJECT

public:
    Playlist(QObject *parent = nullptr);
    ~Playlist();

    void setIndex(int index);
    int index() const;

    void setLoop(bool loop);
    bool isLoop() const;

    void setShuffle(bool shuffle);
    bool isShuffle() const;

    void changeIndex(int index);

    Audio * audioAt(int index);
    Audio * currentAudio();

    void create(Audios *audios);

public slots:
    void next();
    void previous();

signals:
    void indexChanged(int index);

private slots:
    void onAudiosRemoved(int index);

private:
    bool isValidIndex(int index);
    int nextIndex();
    int previousIndex();

    void shuffle();
    void unshuffle();

    Audios *m_audios;
    QVector<int> m_indices;
    int m_index;
    bool m_loop;
    bool m_shuffle;
};

#endif // PLAYLIST_HPP
