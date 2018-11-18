#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include "core/audio.hpp"
#include "core/macros.hpp"
#include "threading/runnable.hpp"

class CoverLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit CoverLoaderWorker(const Audio::vector &audios);

private slots:
    void work() override;

private:
    bool loadCover(Audio *audio);

    Audio::vector m_audios;
};

#endif // COVERLOADERWORKER_HPP
