#include "library.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Library::Library(QObject *parent) :
    QObject(parent),
    m_sorted(false),
    pm_audioLoader(new AudioLoader(this)),
    pm_cacheBuilder(new CacheBuilder(this))
{
    connect(pm_audioLoader, SIGNAL(loaded(Audio *)), this, SLOT(insert(Audio *)));
    connect(pm_audioLoader, SIGNAL(finished()), this, SLOT(onAudioLoaderFinished()));
    connect(pm_audioLoader, SIGNAL(finished()), this, SIGNAL(loaded()));
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
 * Returns the global instance.
 *
 * :return: instance
 */
Library * Library::instance()
{
    if (!_instance)
        _instance = new Library(true, qApp);

    return _instance;
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
 * Loads the library for multiple paths by creating audio builder threads. It
 * checks if the paths have already been loaded and ignores them if they have.
 * This function should not be called twice because it might create database
 * problems.
 *
 * :param paths: paths
 */
void Library::load(const StringList &paths)
{
    pm_audioLoader->setFiles(uniqueFiles(paths));
    pm_audioLoader->start();
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
 * Gets called when the library is loaded and creates the cache builder.
 */
void Library::onAudioLoaderFinished()
{
    pm_cacheBuilder->setAudios(m_audios);
    pm_cacheBuilder->start();
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

/*
 * Loads unique files from paths. Prevents double loading a path.
 *
 * :param paths: paths
 */
StringList Library::uniqueFiles(const StringList &paths)
{
    StringList files;
    for (const QString &path : paths)
    {
        if (!m_paths.contains(path))
        {
            files << FileUtil::glob(path, "mp3");
            m_paths << path;
        }
        else
        {
            Logger::log("Library: Path has already been loaded %1", {path});
        }
    }
    return files;
}

/*
 * Global library instance.
 */
Library * Library::_instance = nullptr;
