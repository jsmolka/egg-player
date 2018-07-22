#ifndef COVERLOADERWORKER_HPP
#define COVERLOADERWORKER_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "cache.hpp"
#include "types.hpp"

class CoverLoaderWorker : public AbstractThread
{
    Q_OBJECT

public:
    CoverLoaderWorker(QObject *parent = nullptr);
    CoverLoaderWorker(const Audios &audios, QObject *parent = nullptr);
    ~CoverLoaderWorker();

    void setAudios(const Audios &audios);
    Audios audios() const;

signals:
    void loaded(Audio *audio, QPixmap cover);

protected:
    void run() override;

private:
    Audios m_audios;
};

#endif // COVERLOADERWORKER_HPP
