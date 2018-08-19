#ifndef AUDIOLOADERWORKER_HPP
#define AUDIOLOADERWORKER_HPP

#include "abstractworker.hpp"
#include "audio.hpp"

class AudioLoaderWorker : public AbstractWorker
{
    Q_OBJECT

public:
    explicit AudioLoaderWorker(QObject *parent = nullptr);
    explicit AudioLoaderWorker(const Files &files, QObject *parent = nullptr);
    ~AudioLoaderWorker();

    void setFiles(const Files &files);
    Files files() const;

signals:
    void loaded(Audio *audio);

public slots:
    void work() override;

private:
    Files m_files;
    AudioVector m_uncached;
    AudioVector m_outdated;
};

#endif // AUDIOLOADERWORKER_HPP
