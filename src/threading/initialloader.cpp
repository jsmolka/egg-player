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
#ifdef QT_DEBUG
    const int threads = 1;
#else
    const int threads = QThread::idealThreadCount();
#endif

    for (const Files &chunk : chunk<Path>(m_files, threads))
    {
        InitialLoaderWorker *worker = new InitialLoaderWorker(chunk);
        connect(worker, &InitialLoaderWorker::loaded, this, &InitialLoader::loaded);
        runWorker(worker);
    }
}
