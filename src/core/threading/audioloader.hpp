#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "logger.hpp"
#include "utils.hpp"

class AudioLoader : public AbstractThread
{
    Q_OBJECT

public:
    AudioLoader(QObject *parent = nullptr);
    AudioLoader(const QStringList &files, QObject *parent = nullptr);
    ~AudioLoader();

    void setFiles(const QStringList &paths);

signals:
    void loaded(Audio *);

protected:
    void run() override;

private:
    QStringList m_files;
};
#endif // AUDIOLOADER_HPP
