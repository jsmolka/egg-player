#include "library.hpp"

/*
 * Constructor.
 */
Library::Library()
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
 * Checks if library is empty.
 *
 * :return: empty
 */
bool Library::isEmpty() const
{
    return m_audios.isEmpty();
}

/*
 * Sorts by title.
 */
void Library::sortByTitle()
{
    m_audios.sortByTitle();
}

/*
 * Loads library from multiple paths.
 * Also creates a thread for cache loading.
 *
 * :param paths: paths
 */
void Library::load(const QStringList &paths)
{
    for (const QString &path : paths)
    {
        if (Utils::exists(path))
            loadFromPath(path);
        else
            Logger::log("Library: Path does not exist '%1'", {path});
    }

    CacheBuilder *builder = new CacheBuilder(m_audios);
    builder->start();
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
 * Loads audios from a path.
 *
 * :param path: path
 */
void Library::loadFromPath(const QString &path)
{
    QStringList files = Utils::glob(path, "*.mp3");
    if (files.isEmpty())
    {
        Logger::log("Library: Path contains no audio files '%1'", {path});
        return;
    }

    m_audios.reserve(m_audios.size() + files.size());
    for (const QString &file : files)
    {
        Audio *audio = new Audio(file);
        if (audio->isValid())
            m_audios << audio;
        else
            delete audio;

    }
}
