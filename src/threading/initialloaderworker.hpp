#ifndef INITIALLOADERWORKER_HPP
#define INITIALLOADERWORKER_HPP

#include "audio.hpp"
#include "runnable.hpp"
#include "types.hpp"

class InitialLoaderWorker : public Runnable
{
    Q_OBJECT

public:
    explicit InitialLoaderWorker(QObject *parent = nullptr);
    explicit InitialLoaderWorker(const Files &files, QObject *parent = nullptr);

    void setFiles(const Files &files);
    Files files() const;

signals:
    void loaded(Audio *audio);

private slots:
    void work() override;

private:
    Files m_files;
};

#endif // INITIALLOADERWORKER_HPP
