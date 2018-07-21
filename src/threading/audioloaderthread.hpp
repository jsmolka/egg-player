#ifndef AUDIOLOADERTHREAD_HPP
#define AUDIOLOADERTHREAD_HPP

#include <QApplication>

#include "abstractthread.hpp"
#include "audio.hpp"
#include "audioloaderworker.hpp"
#include "cache.hpp"
#include "threadpool.hpp"
#include "util.hpp"

class AudioLoaderThread : public AbstractThread
{
    Q_OBJECT

public:
    AudioLoaderThread(QObject *parent = nullptr);
    ~AudioLoaderThread();

    void setFiles(const QVector<QString> &files);
    QVector<QString> files() const;

signals:
    void loaded(Audio *audio);

protected:
    void run() override;

private slots:
    void onWorkerLoaded(Audio *audio, bool cached);

private:
    Cache m_cache;
    ThreadPool m_pool;
    QVector<QString> m_files;
};

#endif // AUDIOLOADERTHREAD_HPP
