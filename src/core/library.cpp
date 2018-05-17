#include "library.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Library::Library(QObject *parent) :
    QObject(parent),
    m_sorted(false),
    pm_cacheBuilder(new CacheBuilder(this)),
    pm_audioLoader(new AudioLoader(this))
{
    connect(pm_audioLoader, SIGNAL(finished()), this, SLOT(onAudioLoaderFinished()));
    connect(pm_audioLoader, SIGNAL(finished()), this, SIGNAL(loaded()));
    connect(pm_audioLoader, SIGNAL(loaded(Audio*)), this, SLOT(insert(Audio*)));
}

/*
 * Destructor.
 */
Library::~Library()
{
    while (!m_audios.isEmpty())
        delete m_audios.takeFirst();
}

/*
 * Setter for sorted property.
 *
 * :param sorted: sorted
 */
void Library::setSorted(bool sorted)
{
    m_sorted = sorted;
}

/*
 * Getter for sorted property.
 *
 * :return: sorted
 */
bool Library::isSorted() const
{
    return m_sorted;
}

/*
 * Getter for audios property.
 *
 * :return: audios
 */
Audios Library::audios() const
{
    return m_audios;
}

/*
 * Loads the library by creating an audio
 * builder. This function should not be called
 * multiple times for the same paths.
 *
 * :param paths: paths
 */
void Library::load(const QStringList &paths)
{
    pm_audioLoader->setPaths(paths);
    pm_audioLoader->start();
}

/*
 * Inserts an audio into the library. Depeding on
 * the sorted propery it will be inserted binary.
 *
 * :param audio: audio
 */
void Library::insert(Audio *audio)
{
    if (m_sorted)
        insertBinary(audio);
    else
        append(audio);
}

/*
 * Starts the cache builder.
 */
void Library::onAudioLoaderFinished()
{
    pm_cacheBuilder->setAudios(m_audios);
    pm_cacheBuilder->start();
}

/*
 * Gets the lower bound for an audio using a
 * binary search like approach.
 *
 * :param audio: audio
 */
int Library::lowerBound(Audio *audio)
{
    int low = 0;
    int high = m_audios.size();
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (audio->title().compare(m_audios[mid]->title(), Qt::CaseInsensitive) < 0)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

/*
 * Inserts audio in library. Keeps it sorted.
 *
 * :param audio: audio
 * :emit inserted: audio, index
 */
void Library::insertBinary(Audio *audio)
{
    int index = lowerBound(audio);
    m_audios.insert(index, audio);
    emit inserted(audio, index);
}

/*
 * Appends audio to libray.
 *
 *
 * :param audio: audio
 * :emit inserted: audio, -1
 */
void Library::append(Audio *audio)
{
    m_audios << audio;
    emit inserted(audio, -1);
}
