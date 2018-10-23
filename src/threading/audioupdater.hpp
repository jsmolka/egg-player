#ifndef AUDIOUPDATER_HPP
#define AUDIOUPDATER_HPP

#include "audio.hpp"
#include "dbaudio.hpp"
#include "dbcover.hpp"
#include "callable.hpp"

class AudioUpdater : public Callable
{
    Q_OBJECT

public:
    explicit AudioUpdater(QObject *parent = nullptr);

signals:
    void updated(Audio *audio);

public slots:
    void update(Audio *audio);

private:
    DbAudio m_dbAudio;
    DbCover m_dbCover;
};

#endif // AUDIOUPDATER_HPP
