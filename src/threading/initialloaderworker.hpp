#ifndef INITIALLOADERWORKER_HPP
#define INITIALLOADERWORKER_HPP

#include "core/audio.hpp"
#include "core/globals.hpp"
#include "threading/core/runnable.hpp"

class InitialLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit InitialLoaderWorker(QObject *parent = nullptr);
    explicit InitialLoaderWorker(const QStrings &files, QObject *parent = nullptr);

    void setFiles(const QStrings &files);
    QStrings files() const;

signals:
    void loaded(Audio *audio);

private slots:
    void work() override;

private:
    QStrings m_files;
};

#endif // INITIALLOADERWORKER_HPP
