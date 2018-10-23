#include "initialloaderworker.hpp"

#include <QApplication>

#include "dbaudio.hpp"

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
    DbAudio dbAudio;
    for (const File &file : qAsConst(m_files))
    {
        if (isInterrupted())
            return;

        Audio *audio = new Audio;
        if (dbAudio.getByFile(file))
        {
            dbAudio.assignTo(audio);
        }
        else
        {
            audio->setFile(file);
            audio->update();
            if (!audio->isValid())
            {
                delete audio;
                continue;
            }
        }
        if (!audio->isCached())
        {
            if (isInterrupted())
                return;

            dbAudio.loadFrom(audio);
            dbAudio.insert();
        }
        if (audio->isOutdated())
        {
            if (isInterrupted())
                return;

            audio->update();
            audio->cover().invalidate();

            dbAudio.loadFrom(audio);
            dbAudio.commit();
        }
        audio->moveToThread(qApp->thread());
        emit loaded(audio);
    }
    emit finished();
}
