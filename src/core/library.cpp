#include "library.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Library::Library(QObject *parent) :
    QObject(parent),
    m_sorted(false),
    pm_pool(new ThreadPool(this))
{
    connect(pm_pool, SIGNAL(finished()), this, SLOT(onPoolFinished()));
    connect(pm_pool, SIGNAL(finished()), this, SIGNAL(loaded()));
}

/*
 * Constructor.
 *
 * :param sorted: sorted
 * :param parent: parent, defaul nullptr
 */
Library::Library(bool sorted, QObject *parent) :
    Library(parent)
{
    m_sorted = sorted;
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
 * Loads the library by creating an audio builder. This function should not be
 * called multiple times for the same paths or they will all be loaded.
 *
 * :param paths: paths
 */
void Library::load(const QStringList &paths)
{
    QStringList files;
    for (const QString &path : paths)
        files << Utils::glob(path, "mp3");

    /*
    int count = pm_pool->advisedCount();
    for (int i = 0; i < count; i++)
    {
        AudioLoader *loader = new AudioLoader(files.mid(i * (files.size() / count), files.size() / count));
        connect(loader, SIGNAL(loaded(Audio*)), this, SLOT(insert(Audio*)));
        pm_pool->add(loader);
    }
    */
    AudioLoader *loader = new AudioLoader(files);
    connect(loader, SIGNAL(loaded(Audio*)), this, SLOT(insert(Audio*)));
    pm_pool->add(loader);
    pm_pool->start();
}

/*
 * Inserts an audio into the library. Depeding on the sorted propery it will be
 * inserted binary.
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
 * Gets called when the library is loaded. Creates the cache builder and
 * disconnects to prevent being called again once the cache builder finishes.
 */
void Library::onPoolFinished()
{
    disconnect(pm_pool, SIGNAL(finished()), this, SLOT(onPoolFinished()));
    pm_pool->add(new CacheBuilder(m_audios));
    pm_pool->start();
}

/*
 * Gets the lower bound for an audio using a binary search like approach. This
 * function is used insead of std::lower_bound because it has a better
 * complexity and returns an index instead.
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
 * Inserts audio into the library and keeps it sorted.
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
