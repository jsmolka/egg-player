#ifndef AUDIOLOADERTHREAD_HPP
#define AUDIOLOADERTHREAD_HPP

#include <QApplication>

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
    void loaded(Audios audios);

protected:
    void run() override;

private slots:
    void onWorkerLoaded(Audios audios);

private:
    void fillBuffer(Audios audios);

    Cache m_cache;
    ThreadPool m_pool;
    Files m_files;
    Audios m_buffer;
};

#endif // AUDIOLOADERTHREAD_HPP
