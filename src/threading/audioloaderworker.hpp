#ifndef AUDIOLOADERWORKER_HPP
#define AUDIOLOADERWORKER_HPP

#include <QMutex>
#include <QMutexLocker>

#include "abstractworker.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "types.hpp"

class AudioLoaderWorker : public AbstractWorker
{
    Q_OBJECT

public:
    AudioLoaderWorker(QObject *parent = nullptr);
    AudioLoaderWorker(const Files &files, QObject *parent = nullptr);
    ~AudioLoaderWorker();

    void setFiles(const Files &files);
    Files files() const;

signals:
    void loaded(Audio *audio);

public slots:
    void work() override;

private:
    Files m_files;
    Audios m_audios;
};

#endif // AUDIOLOADERWORKER_HPP
