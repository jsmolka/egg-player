#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include <QObject>

#include "core/audio.hpp"

class Audios : public QObject, private Audio::vector
{
    Q_OBJECT

public:
    explicit Audios(QObject *parent = nullptr);
    explicit Audios(const Audio::vector &vector, QObject *parent = nullptr);

    Audio::vector vector() const;

    using Audio::vector::at;
    using Audio::vector::first;
    using Audio::vector::last;

    using Audio::vector::size;
    using Audio::vector::isEmpty;
    using Audio::vector::indexOf;

    using Audio::vector::clear;
    using Audio::vector::reserve;

    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);
    void move(int from, int to);

    Audios::iterator insert(Audios::iterator before, Audio *audio);
    Audios::iterator erase(Audios::iterator position);

    using Audio::vector::begin;
    using Audio::vector::end;

    using Audio::vector::cbegin;
    using Audio::vector::cend;

    Audios &operator<<(Audio *audio);
    using Audio::vector::operator[];

    Audios *currentState();

public slots:
    void removeAudio(Audio *audio);

signals:
    void inserted(int index);
    void removed(int index);
    void removedAudio(Audio *audio);
    void moved(int from, int to);
    void updated(int index);
};

#endif // AUDIOS_HPP
