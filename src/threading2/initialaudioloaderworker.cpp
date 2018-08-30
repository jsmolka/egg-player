#include "initialaudioloaderworker.hpp"

#include <QApplication>
#include <QMutex>
#include <QMutexLocker>

#include "cache.hpp"

InitialAudioLoaderWorker::InitialAudioLoaderWorker(QObject *parent)
    : InitialAudioLoaderWorker(Files(), parent)
{

}

InitialAudioLoaderWorker::InitialAudioLoaderWorker(const Files &files, QObject *parent)
    : Runnable(parent)
    , m_files(files)
{

}

void InitialAudioLoaderWorker::setFiles(const Files &files)
{
    m_files = files;
}

Files InitialAudioLoaderWorker::files() const
{
    return m_files;
}

void InitialAudioLoaderWorker::work()
{
    Cache cache;
    for (const File &file : qAsConst(m_files))
    {
        if (isInterrupted())
            return;

        Audio *audio = cache.loadAudio(file);
        if (!audio)
            audio = new Audio(file);

        if (audio->isValid())
        {
            if (!audio->isCached())
            {
                m_uncached << audio;
            }
            if (audio->isOutdated())
            {
                audio->update();
                audio->cover().setId(0);
                m_outdated << audio;
            }
            audio->moveToThread(qApp->thread());
            emit loaded(audio);
        }
        else
        {
            delete audio;
        }
    }

    for (Audio *audio : qAsConst(m_uncached))
    {
        if (isInterrupted())
            return;

        static QMutex mutex;
        const QMutexLocker locker(&mutex);

        cache.insertAudio(audio);
    }

    for (Audio *audio : qAsConst(m_outdated))
    {
        if (isInterrupted())
            return;

        cache.updateAudio(audio);
    }

    emit finished();
}
