#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include "audio.hpp"
#include "runnable.hpp"

class CoverLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit CoverLoaderWorker(QObject *parent = nullptr);
    explicit CoverLoaderWorker(const Audio::vector &audios, QObject *parent = nullptr);

    void setAudios(const Audio::vector &audios);
    Audio::vector audios() const;

private slots:
    void work() override;

private:
    Audio::vector m_audios;
};

#endif // COVERLOADERWORKER_HPP
