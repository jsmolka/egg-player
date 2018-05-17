#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include <QApplication>
#include <QThread>

#include "audio.hpp"
#include "logger.hpp"
#include "utils.hpp"

class AudioLoader : public QThread
{
    Q_OBJECT

public:
    AudioLoader(QObject *parent = nullptr);
    AudioLoader(const QStringList &paths, QObject *parent = nullptr);
    ~AudioLoader();

    void setPaths(const QStringList &paths);

public slots:
    void abort();

signals:
    void loaded(Audio *);

protected:
    void run() override;

private:
    void load(const QString &path);

    bool m_abort;
    QStringList m_paths;
};
#endif // AUDIOLOADER_HPP
