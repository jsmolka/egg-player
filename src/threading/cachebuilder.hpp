#ifndef CACHEBUILDER_HPP
#define CACHEBUILDER_HPP

#include "abstractthread.hpp"
#include "audio.hpp"
#include "cache.hpp"

class CacheBuilder : public AbstractThread
{
    Q_OBJECT

public:
    CacheBuilder(QObject *parent = nullptr);
    CacheBuilder(const Audios &audios, QObject *parent = nullptr);
    ~CacheBuilder();

    void setAudios(const Audios &audios);

protected:
    void run() override;

private:
    Audios m_audios;
};

#endif // CACHEBUILDER_HPP
