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

    Audios::iterator insert(Audios::iterator before, Audio *audio);
    Audios::iterator erase(Audios::iterator position);

    using Audio::vector::begin;
    using Audio::vector::end;

    using Audio::vector::cbegin;
    using Audio::vector::cend;

    int lowerBound(Audio *audio);

    Audios *currentState();

    using Audio::vector::operator[];
    Audios &operator<<(Audio *audio);

public slots:
    void removeAudio(Audio *audio);

signals:
    void inserted(int index);
    void removed(int index);
    void updated(int index);
    void removedAudio(Audio *audio);
};

#endif // AUDIOS_HPP
