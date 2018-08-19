#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include "abstractworker.hpp"
#include "audio.hpp"

class CoverLoaderWorker : public AbstractWorker
{
    Q_OBJECT

public:
    explicit CoverLoaderWorker(QObject *parent = nullptr);
    explicit CoverLoaderWorker(const AudioVector &audios, QObject *parent = nullptr);
    ~CoverLoaderWorker();

    void setAudios(const AudioVector &audios);
    AudioVector audios() const;

public slots:
    void work() override;

private:
    AudioVector m_audios;
};

#endif // COVERLOADERWORKER_HPP
