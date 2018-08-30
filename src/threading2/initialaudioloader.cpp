#include "initialaudioloader.hpp"

#include "initialaudioloaderworker.hpp"

InitialAudioLoader::InitialAudioLoader(QObject *parent)
    : InitialAudioLoader(Files(), parent)
{

}

InitialAudioLoader::InitialAudioLoader(const Files &files, QObject *parent)
    : Controller(parent)
    , m_files(files)
{

}

void InitialAudioLoader::setFiles(const Files &files)
{
    m_files = files;
}

Files InitialAudioLoader::files() const
{
    return m_files;
}

void InitialAudioLoader::start()
{
    for (const Files &chunk : chunk<Path>(m_files, QThread::idealThreadCount()))
    {
        InitialAudioLoaderWorker *worker = new InitialAudioLoaderWorker(chunk);
        connect(worker, &InitialAudioLoaderWorker::loaded, this, &InitialAudioLoader::loaded);
        runWorker(worker);
    }
}
