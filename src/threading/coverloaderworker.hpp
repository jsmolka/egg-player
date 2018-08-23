#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include "abstractworker.hpp"
#include "audio.hpp"

class CoverLoaderWorker : public AbstractWorker
{
    Q_OBJECT

public:
    explicit CoverLoaderWorker(QObject *parent = nullptr);
    explicit CoverLoaderWorker(const Audio::vector &audios, QObject *parent = nullptr);
    ~CoverLoaderWorker();

    void setAudios(const Audio::vector &audios);
    Audio::vector audios() const;

public slots:
    void work() override;

private:
    Audio::vector m_audios;
};

#endif // COVERLOADERWORKER_HPP
