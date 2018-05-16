#include "library.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Library::Library(QObject *parent) :
    QObject(parent)
{

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
 * Getter for audios property.
 *
 * :return: audios
 */
Audios Library::audios() const
{
    return m_audios;
}

/*
 * Getter for paths property.
 *
 * :return: paths
 */
QStringList Library::paths() const
{
    return m_paths;
}

/*
 * Sorts by title.
 */
void Library::sortByTitle()
{
    m_audios.sortByTitle();
}

/*
 * Loads library from multiple paths. Creates a
 * library builder thread and returns immediately.
 *
 * :param paths: paths
 */
void Library::load(const QStringList &paths)
{
    m_paths << paths;

    pm_libraryBuilder = new AudioLoader(m_paths, this);
    connect(pm_libraryBuilder, SIGNAL(finished()), this, SLOT(onLibraryBuilderFinished()));
    connect(pm_libraryBuilder, SIGNAL(finished()), this, SIGNAL(loaded()));
    connect(pm_libraryBuilder, SIGNAL(audioLoaded(Audio*)), this, SLOT(insert(Audio*)));
    pm_libraryBuilder->start();
}

/*
 * Overloaded function.
 *
 * :param path: path
 */
void Library::load(const QString &path)
{
    load(QStringList(path));
}

/*
 * Searches for a string in the library.
 *
 * :param string: string
 * :param cs: case sensivity, default insensitive
 * :return: audios
 */
Audios Library::search(const QString &string, Qt::CaseSensitivity cs)
{
    Audios result;
    for (Audio *audio : m_audios)
        if (audio->title().contains(string, cs)
                || audio->artist().contains(string, cs)
                || audio->album().contains(string, cs))
            result << audio;
    return result;
}

/*
 * Returns audio at index.
 *
 * :param index: index
 * :return: audio, nullptr if invalid index
 */
Audio * Library::audioAt(int index)
{
    if (index < 0 || index >= m_audios.size())
        return nullptr;

    return m_audios[index];
}

/*
 * Inserts audio into library.
 *
 * :param audio: audio
 */
void Library::insert(Audio *audio)
{
    m_audios << audio;
}

/*
 * Library builder finished event. Starts the
 * cache builder.
 */
void Library::onLibraryBuilderFinished()
{
    pm_cacheBuilder = new CacheBuilder(m_audios, this);
    pm_cacheBuilder->start();
}
