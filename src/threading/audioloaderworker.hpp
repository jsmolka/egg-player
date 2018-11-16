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

    EGG_CPROP(QStrings, files, setFiles, files)

signals:
    void loaded(Audio *audio);

private slots:
    void work() override;

private:
    bool insertAudio(Audio *audio) const;
    bool updateAudio(Audio *audio) const;

};

#endif // AUDIOLOADERWORKER_HPP
