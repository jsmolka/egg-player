#ifndef AUDIOLOADER_HPP
#define AUDIOLOADER_HPP

#include "audio.hpp"
#include "callable.hpp"
#include "dbaudio.hpp"
#include "dbcover.hpp"
#include "types.hpp"

class AudioLoader : public Callable
{
    Q_OBJECT

public:
    explicit AudioLoader(QObject *parent = nullptr);

public slots:
    void load(const File &file);

signals:
    void loaded(Audio *audio);

private:
    DbAudio m_dbAudio;
    DbCover m_dbCover;
};

#endif // AUDIOLOADER_HPP
