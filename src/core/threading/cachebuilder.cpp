#include "cachebuilder.hpp"

/*
 * Constructor.
 *
 * param parent: parent, default nullptr
 */
CacheBuilder::CacheBuilder(QObject *parent) :
    AbstractThread(parent)
{

}

/*
 * Constructor.
 *
 * :param audios: audios
 * :param parent: parent, default nullptr
 */
CacheBuilder::CacheBuilder(const Audios &audios, QObject *parent) :
    AbstractThread(parent),
    m_audios(audios)
{

}

/*
 * Destructor.
 */
CacheBuilder::~CacheBuilder()
{

}

/*
 * Setter for audio property.
 *
 * :param audios: audios
 */
void CacheBuilder::setAudios(const Audios &audios)
{
    m_audios = audios;
}

/*
 * Loads audio covers.
 */
void CacheBuilder::run()
{
    Cache cache;
    for (Audio *audio : m_audios)
    {
        if (isAbort())
            return;

        if (!cache.contains(audio))
            cache.insertCover(audio);
    }
}
