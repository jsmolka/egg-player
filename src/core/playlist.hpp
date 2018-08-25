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
    explicit Playlist(QObject *parent = nullptr);

    void setIndex(int index);
    int index() const;

    bool isLoop() const;
    bool isShuffle() const;

    bool isEmpty() const;

    void changeIndex(int index);

    Audio * audioAt(int index);
    Audio * currentAudio();

    void create(Audios *audios);

public slots:
    void setLoop(bool loop);
    void setShuffle(bool shuffle);

    void next();
    void previous();

signals:
    void indexChanged(int index);

private slots:
    void onAudiosInserted(int index);
    void onAudiosRemoved(int index);

private:
    void createAudios(Audios *audios);
    void createIndices(int size);

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
