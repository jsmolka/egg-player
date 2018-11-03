#include "initialloaderworker.hpp"

#include <QApplication>

#include "core/database/cache.hpp"

InitialLoaderWorker::InitialLoaderWorker(const QStrings &files)
    : m_files(files)
{

}

void InitialLoaderWorker::work()
{
    for (const QString &file : qAsConst(m_files))
    {
        Audio *audio = Cache::loadAudio(file);
        if (!audio)
            continue;

        if (!insertAudio(audio))
            return;

        if (!updateAudio(audio))
            return;

        audio->moveToThread(qApp->thread());
        emit loaded(audio);
    }
    emit finished();
}

bool InitialLoaderWorker::insertAudio(Audio *audio) const
{
    if (isInterrupted())
        return false;

    if (audio->isCached())
        return true;

    return Cache::insertAudio(audio);
}

bool InitialLoaderWorker::updateAudio(Audio *audio) const
{
    if (isInterrupted())
        return false;

    if (!audio->isOutdated())
        return true;

    if (!audio->update())
        return false;

    audio->cover().invalidate();
    return Cache::updateAudio(audio);
}
