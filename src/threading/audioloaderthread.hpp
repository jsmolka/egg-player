#ifndef AUDIOLOADERTHREAD_HPP
#define AUDIOLOADERTHREAD_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "audioloaderworker.hpp"
#include "cache.hpp"
#include "threadpool.hpp"
#include "types.hpp"
#include "util.hpp"

class AudioLoaderThread : public AbstractThread
{
    Q_OBJECT

public:
    AudioLoaderThread(QObject *parent = nullptr);
    AudioLoaderThread(const Files &files, QObject *parent = nullptr);
    ~AudioLoaderThread();

    void setFiles(const Files &files);
    Files files() const;

signals:
    void loaded(Audio *audio);

protected:
    void run() override;

private slots:
    void onWorkerLoaded(Audio *audio);

private:
    void startWorkerThreads();

    Files m_files;
    ThreadPool m_pool;
    Audios m_uncached;
};

#endif // AUDIOLOADERTHREAD_HPP
