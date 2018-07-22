#ifndef COVERLOADERTHREAD_HPP
#define COVERLOADERTHREAD_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "coverloaderworker.hpp"
#include "threadpool.hpp"
#include "util.hpp"

class CoverLoaderThread : public AbstractThread
{
    Q_OBJECT

public:
    CoverLoaderThread(QObject *parent = nullptr);
    CoverLoaderThread(const Audios &audios, QObject *parent = nullptr);
    ~CoverLoaderThread();

    void setAudios(const Audios &audios);
    Audios audios() const;

protected:
    void run() override;

private slots:
    void onWorkerLoaded(Audio *audio, QPixmap cover);

private:
    void startWorkerThreads();

    Audios m_audios;
    ThreadPool m_pool;

    Audios m_uncachedAudios;
    QVector<QPixmap> m_uncachedCover;
};

#endif // COVERLOADERTHREAD_HPP
