#ifndef AUDIOS_STATICVECTOR_HPP
#define AUDIOS_STATICVECTOR_HPP

#include <QObject>

#include "core/audio.hpp"

namespace audios
{

class StaticVector : public QObject, protected Audio::vector
{
    Q_OBJECT

public:
    explicit StaticVector(QObject *parent = nullptr);
    explicit StaticVector(const Audio::vector &vector, QObject *parent = nullptr);
    virtual ~StaticVector() = 0;

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
    void removedAudio(Audio *audio);
};

}

#endif // AUDIOS_STATICVECTOR_HPP
