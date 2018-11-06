#ifndef INITIALLOADERWORKER_HPP
#define INITIALLOADERWORKER_HPP

#include "core/audio.hpp"
#include "core/macros.hpp"
#include "core/types.hpp"
#include "threading/core/runnable.hpp"

class InitialLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit InitialLoaderWorker(const QStrings &files);

    EGG_CPROP(QStrings, files, setFiles, files)

signals:
    void loaded(Audio *audio);

private slots:
    void work() override;

private:
    bool insertAudio(Audio *audio) const;
    bool updateAudio(Audio *audio) const;

};

#endif // INITIALLOADERWORKER_HPP
