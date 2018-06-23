#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include <QVector>

#include "abstractthread.hpp"
#include "audio.hpp"
#include "cache.hpp"

class AudioLoader : public AbstractThread
{
    Q_OBJECT

public:
    AudioLoader(QObject *parent = nullptr);
    AudioLoader(const QVector<QString> &files, QObject *parent = nullptr);
    ~AudioLoader();

    void setFiles(const QVector<QString> &files);

signals:
    void loaded(Audio *);

protected:
    void run() override;

private:
    QVector<QString> m_files;
};

#endif // AUDIOLOADER_HPP
