#include "initialloaderworker.hpp"

#include <QApplication>

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
    for (const File &file : qAsConst(m_files))
    {
        if (isInterrupted())
            return;

        Audio *audio = Cache::loadAudio(file);
        if (!audio)
            continue;

        if (!audio->isCached())
        {
            if (isInterrupted())
                return;

            Cache::insertAudio(audio);
        }
        if (audio->isOutdated())
        {
            if (isInterrupted())
                return;

            audio->update();
            audio->cover().invalidate();
            Cache::updateAudio(audio);
        }
        audio->moveToThread(qApp->thread());
        emit loaded(audio);
    }
    emit finished();
}
