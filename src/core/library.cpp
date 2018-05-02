#include "library.hpp"

/*
 * Constructor. Loads files from the library path
 * and creates a thread for cover caching.
 *
 * :param path: path
 */
Library::Library(const QString &path)
{
    if (!Utils::exists(path))
    {
        Logger::log("Library: Path does not exist '%1'", path);
        return;
    }

    loadFiles(path);

    CacheBuilder *builder = new CacheBuilder(m_audios);
    builder->start();
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
 * Searches for a string in the library.
 *
 * :param string: string
 * :param cs: case sensivity, default insensitive
 * :return: audio list
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
 * Loads library files.
 *
 * :param path: path
 */
void Library::loadFiles(const QString &path)
{
    QStringList files = Utils::glob(path, "*.mp3");
    if (files.isEmpty())
    {
        Logger::log("Library: Path contains no files '%1'", path);
        return;
    }

    m_audios.reserve(files.size());
    for (const QString &file : files)
    {
        Audio *audio = new Audio(file);
        if (!audio->isValid())
        {
            delete audio;
            continue;
        }
        m_audios << audio;
    }
}
