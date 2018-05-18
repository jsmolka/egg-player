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
    AudioLoader(const QStringList &paths, QObject *parent = nullptr);
    ~AudioLoader();

    void setPaths(const QStringList &paths);

signals:
    void loaded(Audio *);

protected:
    void run() override;

private:
    void load(const QString &path);

    QStringList m_paths;
};
#endif // AUDIOLOADER_HPP
