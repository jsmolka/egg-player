#include "library.hpp"

/*
 * Constructor. Loads file from the
 * library path.
 *
 * :param path: library path
 */
Library::Library(const QString &path)
{
    if (FileUtil::exists(path))
        loadFiles(path);
    else
        Logger::log("Library: Path does not exist '%1'", path);
}

/*
 * Destructor.
 */
Library::~Library()
{
    for (Audio *audio : m_audioList)
        delete audio;
}

/*
 * Getter for audio list property.
 *
 * :return: audio list
 */
AudioList Library::audioList() const
{
    return m_audioList;
}

/*
 * Checks if library is empty.
 *
 * :return: empty
 */
bool Library::isEmpty() const
{
    return m_audioList.isEmpty();
}

/*
 * Searches for a string in the library.
 *
 * :param string: string
 * :param cs: case sensive
 * :return: list of audio pointer
 */
AudioList Library::search(const QString &string, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->title().contains(string, cs)
                || audio->artist().contains(string, cs)
                || audio->album().contains(string, cs))
            result << audio;
    return result;
}

/*
 * Sorts by title.
 */
void Library::sortByTitle()
{
    m_audioList.sortByTitle();
}

/*
 * Returns audio at index.
 *
 * :param index: index
 * :return: audio pointer
 */
Audio * Library::audioAt(int index)
{
    return m_audioList[index];
}

/*
 * Loads library files. Inserts cover into
 * cache if they do not exist already.
 *
 * :param path: path with files
 */
void Library::loadFiles(const QString &path)
{
    QStringList files = FileUtil::glob(path, "*.mp3");
    if (files.isEmpty())
    {
        Logger::log("Library: Path contains no files '%1'", path);
        return;
    }

    Cache cache;
    cache.connect();

    for (const QString &file : files)
    {
        Audio *audio = new Audio(file);
        if (!audio->isValid())
        {
            delete audio;
            continue;
        }

        if (!cache.exists(audio))
            cache.insert(audio);

        m_audioList << audio;
    }
    cache.close();
}
