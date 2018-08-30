#ifndef INITIALAUDIOLOADERWORKER_HPP
#define INITIALAUDIOLOADERWORKER_HPP

#include "audio.hpp"
#include "runnable.hpp"
#include "types.hpp"

class InitialAudioLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit InitialAudioLoaderWorker(QObject *parent = nullptr);
    explicit InitialAudioLoaderWorker(const Files &files, QObject *parent = nullptr);

    void setFiles(const Files &files);
    Files files() const;

signals:
    void loaded(Audio *audio);

private slots:
    void work();

private:
    Files m_files;
    Audio::vector m_uncached;
    Audio::vector m_outdated;
};

#endif // INITIALAUDIOLOADERWORKER_HPP
