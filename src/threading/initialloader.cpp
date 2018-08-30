#include "initialloader.hpp"

#include "initialloaderworker.hpp"

InitialLoader::InitialLoader(QObject *parent)
    : InitialLoader(Files(), parent)
{

}

InitialLoader::InitialLoader(const Files &files, QObject *parent)
    : Controller(parent)
    , m_files(files)
{

}

void InitialLoader::setFiles(const Files &files)
{
    m_files = files;
}

Files InitialLoader::files() const
{
    return m_files;
}

void InitialLoader::start()
{
    for (const Files &chunk : chunk<Path>(m_files, QThread::idealThreadCount()))
    {
        InitialLoaderWorker *worker = new InitialLoaderWorker(chunk);
        connect(worker, &InitialLoaderWorker::loaded, this, &InitialLoader::loaded);
        runWorker(worker);
    }
}
