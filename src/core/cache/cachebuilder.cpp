#include "cachebuilder.hpp"

/*
 * Constructor. Connects the thread to the app
 * so that it automatically aborts and deletes.
 *
 * :param parent: parent, default nullptr
 * :param audios: audios
 */
CacheBuilder::CacheBuilder(const Audios &audios, QObject *parent) :
    QThread(parent)
{
    m_audios = audios;
    m_abort = false;

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(abort()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

/*
 * Destructor.
 */
CacheBuilder::~CacheBuilder()
{

}

/*
 * Sets the abort property and cleanly exits
 * the thread.
 */
void CacheBuilder::abort()
{
    m_abort = true;
    quit();
    wait();
}

/*
 * Implemented run function. This is the main
 * function of the thread. It loads the audio
 * covers and saves them in the cache.
 */
void CacheBuilder::run()
{
    Cache cache;
    for (Audio *audio : m_audios)
    {
        if (m_abort)
            break;

        if (!cache.contains(audio))
            cache.insert(audio);
    }
}
