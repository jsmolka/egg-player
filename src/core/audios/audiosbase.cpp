#include "audiosbase.hpp"

audios::AudiosBase::AudiosBase(QObject *parent)
    : AudiosBase(QVector<Audio>(), parent)
{

}

audios::AudiosBase::AudiosBase(const QVector<Audio> &vector, QObject *parent)
    : QObject(parent)
    , ReadableVector<Audio>(vector)
{

}

audios::AudiosBase::~AudiosBase()
{

}

QVector<Audio> audios::AudiosBase::vector() const
{
    return static_cast<QVector<Audio>>(*this);
}
