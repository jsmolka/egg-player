#ifndef AUDIOS_FROZENVECTOR_HPP
#define AUDIOS_FROZENVECTOR_HPP

#include <QObject>

#include "core/audio.hpp"

namespace audios
{

class FrozenVector : public QObject, protected Audio::vector
{
    Q_OBJECT

public:
    explicit FrozenVector(QObject *parent = nullptr);
    explicit FrozenVector(const Audio::vector &vector, QObject *parent = nullptr);
    virtual ~FrozenVector() = 0;

    Audio::vector vector() const;

    using Audio::vector::at;
    using Audio::vector::first;
    using Audio::vector::last;

    using Audio::vector::size;
    using Audio::vector::isEmpty;
    using Audio::vector::indexOf;

    using Audio::vector::begin;
    using Audio::vector::end;

    using Audio::vector::cbegin;
    using Audio::vector::cend;

    using Audio::vector::operator[];

signals:
    void removed(int index);
    void removedAudio(Audio audio);
};

}

#endif // AUDIOS_FROZENVECTOR_HPP
