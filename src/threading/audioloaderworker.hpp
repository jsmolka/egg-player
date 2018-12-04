#ifndef AUDIOLOADERWORKER_HPP
#define AUDIOLOADERWORKER_HPP

#include "core/audio.hpp"
#include "core/macros.hpp"
#include "core/types.hpp"
#include "threading/runnable.hpp"

class AudioLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit AudioLoaderWorker(const QStrings &files);

signals:
    void loaded(Audio audio);

private slots:
    void work() override;

private:
    bool insertAudio(Audio &audio) const;
    bool updateAudio(Audio &audio) const;

    QStrings m_files;
};

#endif // AUDIOLOADERWORKER_HPP
