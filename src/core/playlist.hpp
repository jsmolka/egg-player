#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <QObject>
#include <QVector>

#include "core/audio.hpp"
#include "core/audios/currentstate.hpp"

class Playlist : public QObject
{
    Q_OBJECT

public:
    explicit Playlist(QObject *parent = nullptr);

    bool isLoop() const;
    bool isShuffle() const;
    bool isEmpty() const;

    int index() const;
    int size() const;

    Audio *audioAt(int index);
    Audio *currentAudio();

    void next();
    void previous();

    void loadFromState(audios::CurrentState *state, int index = 0);

public slots:
    void setLoop(bool loop);
    void setShuffle(bool shuffle);

signals:
    void audioChanged(Audio *audio);
    void endReached();

private slots:
    void onStateRemoved(int index);

private:
    using Indices = QVector<int>;

    void setState(audios::CurrentState *state);
    void createIndices(int size);

    void changeIndex(int index);
    int nextIndex();
    int previousIndex();

    void shuffle();
    void unshuffle();

    audios::CurrentState *m_state;
    Indices m_indices;
    int m_index;
    bool m_loop;
    bool m_shuffle;
};

#endif // PLAYLIST_HPP
