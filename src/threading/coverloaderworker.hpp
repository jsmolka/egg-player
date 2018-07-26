#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include <QMutex>
#include <QMutexLocker>

#include "abstractworker.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "types.hpp"

class CoverLoaderWorker : public AbstractWorker
{
    Q_OBJECT

public:
    CoverLoaderWorker(QObject *parent = nullptr);
    CoverLoaderWorker(const Audios &audios, QObject *parent = nullptr);
    ~CoverLoaderWorker();

    void setAudios(const Audios &audios);
    Audios audios() const;

public slots:
    void work() override;

private:
    Audios m_audios;
};

#endif // COVERLOADERWORKER_HPP
