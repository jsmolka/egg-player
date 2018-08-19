#ifndef AUDIOLOADERWORKER_HPP
#define AUDIOLOADERWORKER_HPP

#include "abstractworker.hpp"
#include "audio.hpp"

class AudioLoaderWorker : public AbstractWorker
{
    Q_OBJECT

public:
    explicit AudioLoaderWorker(QObject *parent = nullptr);
    explicit AudioLoaderWorker(const Paths &paths, QObject *parent = nullptr);
    ~AudioLoaderWorker();

    void setPaths(const Paths &paths);
    Paths paths() const;

signals:
    void loaded(Audio *audio);

public slots:
    void work() override;

private:
    Paths m_paths;
    AudioVector m_uncached;
    AudioVector m_outdated;
};

#endif // AUDIOLOADERWORKER_HPP
