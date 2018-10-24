#include "initialloaderworker.hpp"

#include <QApplication>

#include "core/database/cache.hpp"

InitialLoaderWorker::InitialLoaderWorker(QObject *parent)
    : InitialLoaderWorker(QStrings(), parent)
{

}

InitialLoaderWorker::InitialLoaderWorker(const QStrings &files, QObject *parent)
    : Runnable(parent)
    , m_files(files)
{

}

void InitialLoaderWorker::setFiles(const QStrings &files)
{
    m_files = files;
}

QStrings InitialLoaderWorker::files() const
{
    return m_files;
}

void InitialLoaderWorker::work()
{
    for (const QString &file : qAsConst(m_files))
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
