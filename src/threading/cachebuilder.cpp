#include "cachebuilder.hpp"

CacheBuilder::CacheBuilder(QObject *parent)
    : AbstractThread(parent)
{

}

CacheBuilder::CacheBuilder(const Audios &audios, QObject *parent)
    : AbstractThread(parent)
    , m_audios(audios)
{

}

CacheBuilder::~CacheBuilder()
{

}

void CacheBuilder::setAudios(const Audios &audios)
{
    m_audios = audios;
}

void CacheBuilder::run()
{
    Cache cache;
    for (Audio *audio : m_audios)
    {
        if (isAbort())
            return;

        if (audio->coverId() == -1)
        {
            int id = cache.coverId(audio);
            if (id == -1)
                id = cache.insertCover(audio);

            audio->setCoverId(id);
        }
    }
}
