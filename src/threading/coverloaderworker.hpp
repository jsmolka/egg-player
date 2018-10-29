#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include "core/audio.hpp"
#include "core/globals.hpp"
#include "threading/core/runnable.hpp"

class CoverLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit CoverLoaderWorker(QObject *parent = nullptr);
    explicit CoverLoaderWorker(const Audio::vector &audios, QObject *parent = nullptr);

    EGG_CPROP(Audio::vector, audios, setAudios, audios)

private slots:
    void work() override;

private:
    bool loadCover(Audio *audio);
};

#endif // COVERLOADERWORKER_HPP
