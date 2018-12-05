#ifndef AUDIOFINDER_HPP
#define AUDIOFINDER_HPP

#include <QObject>
#include <QTimer>

#include "audios.hpp"

class AudioFinder : public QObject
{
    Q_OBJECT

public:
    explicit AudioFinder(QObject *parent = nullptr);

    void setAudios(Audios *audios);
    void addKey(const QString &key);

    int find();

private slots:
    void reset();

private:
    Audios *m_audios;
    QString m_string;
    QTimer m_reset;
    int m_index;
};

#endif // AUDIOFINDER_HPP
