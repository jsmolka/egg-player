#ifndef AUDIOLOADERWORKER_HPP
#define AUDIOLOADERWORKER_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "cache.hpp"

class AudioLoaderWorker : public AbstractThread
{
    Q_OBJECT

public:
    AudioLoaderWorker(QObject *parent = nullptr);
    ~AudioLoaderWorker();

    void setFiles(const QVector<QString> &files);
    QVector<QString> files() const;

signals:
    void loaded(Audio *audio, bool cached);

protected:
    void run() override;

private:
    QVector<QString> m_files;
};

#endif // AUDIOLOADERWORKER_HPP
