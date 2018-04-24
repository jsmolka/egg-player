#include "cachebuilder.hpp"

/*
 * Constructor.
 *
 * :param audioList: audio list
 */
CacheBuilder::CacheBuilder(const AudioList &audioList)
{
    m_audioList = audioList;
    m_abort = false;

    // Abort and delete thread at applicaton end
    connect(QApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(abort()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

/*
 * Destructor.
 */
CacheBuilder::~CacheBuilder()
{

}

/*
 * Sets the abort property and cleanly
 * exits the thread.
 */
void CacheBuilder::abort()
{
    m_abort = true;
    quit();
    wait();
}

/*
 * Implemented run function. This is
 * the main function of the thread. It
 * loads the cover files and aborts the
 * thread if necessary.
 */
void CacheBuilder::run()
{
    Cache cache;
    for (Audio *audio : m_audioList)
    {
        if (!cache.contains(audio))
            cache.insert(audio);
        if (m_abort)
            break;
    }
}
