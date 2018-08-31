#include "audioloader.hpp"

#include <QApplication>
#include <QMutex>
#include <QMutexLocker>

AudioLoader::AudioLoader(QObject *parent)
    : Callable(parent)
{

}

void AudioLoader::load(const File &file)
{
    Audio *audio = m_cache.loadAudio(file);
    if (!audio)
        audio = new Audio(file);

    if (!audio->isValid())
        delete audio;
    if (!audio->isCached())
    {
        if (isInterrupted())
            return;

        static QMutex mutex;
        const QMutexLocker locker(&mutex);
        m_cache.insertAudio(audio);
    }
    if (audio->isOutdated())
    {
        if (isInterrupted())
            return;

        audio->update();
        audio->cover().setId(0);
        m_cache.updateAudio(audio);
    }
    if (!audio->cover().isValid())
    {
        if (isInterrupted())
            return;

        const QPixmap cover = Cover::loadFromFile(audio->wideFile());

        static QMutex mutex;
        const QMutexLocker locker(&mutex);

        const int id = m_cache.insertCover(cover);
        if (id > 0)
            m_cache.setAudioCoverId(audio, id);
    }
    audio->moveToThread(qApp->thread());
    emit loaded(audio);
}
