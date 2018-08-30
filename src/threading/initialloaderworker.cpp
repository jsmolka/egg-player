#include "initialloaderworker.hpp"

#include <QApplication>
#include <QMutex>
#include <QMutexLocker>

#include "cache.hpp"

InitialLoaderWorker::InitialLoaderWorker(QObject *parent)
    : InitialLoaderWorker(Files(), parent)
{

}

InitialLoaderWorker::InitialLoaderWorker(const Files &files, QObject *parent)
    : Runnable(parent)
    , m_files(files)
{

}

void InitialLoaderWorker::setFiles(const Files &files)
{
    m_files = files;
}

Files InitialLoaderWorker::files() const
{
    return m_files;
}

void InitialLoaderWorker::work()
{
    Cache cache;
    for (const File &file : qAsConst(m_files))
    {
        if (isInterrupted())
            return;

        Audio *audio = cache.loadAudio(file);
        if (!audio)
            audio = new Audio(file);

        if (!audio->isValid())
        {
            delete audio;
            continue;
        }
        if (!audio->isCached())
        {
            if (isInterrupted())
                return;

            static QMutex mutex;
            const QMutexLocker locker(&mutex);
            cache.insertAudio(audio);
        }
        if (audio->isOutdated())
        {
            if (isInterrupted())
                return;

            audio->update();
            audio->cover().setId(0);
            cache.updateAudio(audio);
        }
        audio->moveToThread(qApp->thread());
        emit loaded(audio);
    }
    emit finished();
}
