#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include <QMutex>
#include <QMutexLocker>

#include "abstractworker.hpp"
#include "audio.hpp"
#include "audios.hpp"
#include "cache.hpp"
#include "types.hpp"

class CoverLoaderWorker : public AbstractWorker
{
    Q_OBJECT

public:
    CoverLoaderWorker(QObject *parent = nullptr);
    CoverLoaderWorker(const AudioVector &audios, QObject *parent = nullptr);
    ~CoverLoaderWorker();

    void setAudios(const AudioVector &audios);
    AudioVector audios() const;

public slots:
    void work() override;

private:
    AudioVector m_audios;
};

#endif // COVERLOADERWORKER_HPP
