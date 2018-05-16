#include "cachebuilder.hpp"

/*
 * Constructor.
 *
 * param parent: parent, default nullptr
 */
CacheBuilder::CacheBuilder(QObject *parent) :
    QThread(parent),
    m_abort(false)
{
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(abort()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

/*
 * Constructor.
 *
 * :param audios: audios
 * :param parent: parent, default nullptr
 */
CacheBuilder::CacheBuilder(const Audios &audios, QObject *parent) :
    CacheBuilder(parent)
{
    m_audios = audios;
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
 * Exits thread cleanly.
 */
void CacheBuilder::abort()
{
    m_abort = true;
    quit();
    wait();
}

/*
 * Loads audio covers.
 */
void CacheBuilder::run()
{
    Cache cache;
    for (Audio *audio : m_audios)
    {
        if (m_abort)
            return;

        if (!cache.contains(audio))
            cache.insert(audio);
    }
}
