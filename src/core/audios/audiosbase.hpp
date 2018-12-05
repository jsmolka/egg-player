#ifndef AUDIOS_AUDIOSBASE_HPP
#define AUDIOS_AUDIOSBASE_HPP

#include <QObject>

#include "core/audio.hpp"
#include "core/readablevector.hpp"

namespace audios
{

class AudiosBase : public QObject, public ReadableVector<Audio>
{
    Q_OBJECT

public:
    explicit AudiosBase(QObject *parent = nullptr);
    explicit AudiosBase(const QVector<Audio> &vector, QObject *parent = nullptr);
    virtual ~AudiosBase() = 0;

    QVector<Audio> vector() const;

signals:
    void removed(int index);
    void removedAudio(Audio audio);
};

}

#endif // AUDIOS_AUDIOSBASE_HPP
