#ifndef AUDIOLOADERWORKER_HPP
#define AUDIOLOADERWORKER_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "types.hpp"

class AudioLoaderWorker : public AbstractThread
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

protected:
    void run() override;

private:
    Files m_files;
};

#endif // AUDIOLOADERWORKER_HPP
