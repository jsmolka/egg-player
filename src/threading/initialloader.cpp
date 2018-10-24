#include "initialloader.hpp"

#include "threading/initialloaderworker.hpp"

InitialLoader::InitialLoader(QObject *parent)
    : InitialLoader(QStrings(), parent)
{

}

InitialLoader::InitialLoader(const QStrings &files, QObject *parent)
    : Controller(parent)
    , m_files(files)
{

}

void InitialLoader::setFiles(const QStrings &files)
{
    m_files = files;
}

QStrings InitialLoader::files() const
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

    for (const QStrings &chunk : chunk<QString>(m_files, threads))
    {
        InitialLoaderWorker *worker = new InitialLoaderWorker(chunk);
        connect(worker, &InitialLoaderWorker::loaded, this, &InitialLoader::loaded);
        runWorker(worker);
    }
}
