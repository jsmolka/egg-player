#include "library.hpp"

/*
 * Constructor.
 *
 * :param audioList: audio list
 * :param parent: parent pointer
 */
CacheBuilder::CacheBuilder(const AudioList &audioList, QObject *parent) : QThread(parent)
{
    m_audioList = audioList;
}

/*
 * Overridden run function. This is
 * the main function of the thread.
 */
void CacheBuilder::run()
{
    Cache cache;
    for (Audio *audio : m_audioList)
        if (!cache.contains(audio))
            cache.insert(audio);
}

/*
 * Constructor. Loads files from library
 * path and creates thread for cover caching.
 *
 * :param path: path
 * :param parent: parent pointer
 */
Library::Library(const QString &path, QObject *parent) : QObject(parent)
{
    if (FileUtil::exists(path))
    {
        loadFiles(path);

        CacheBuilder *builder = new CacheBuilder(m_audioList, this);
        connect(QApplication::instance(), SIGNAL(aboutToQuit()), builder, SLOT(terminate()));
        builder->start();
    }
    else
    {
        Logger::log("Library: Path does not exist '%1'", path);
    }
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
 * Sorts by title.
 */
void Library::sortByTitle()
{
    m_audioList.sortByTitle();
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
 * Loads library files.
 *
 * :param path: path
 */
void Library::loadFiles(const QString &path)
{
    QStringList files = FileUtil::glob(path, "*.mp3");
    if (files.isEmpty())
    {
        Logger::log("Library: Path contains no files '%1'", path);
        return;
    }

    for (const QString &file : files)
    {
        Audio *audio = new Audio(file);
        if (!audio->isValid())
        {
            delete audio;
            continue;
        }

        m_audioList << audio;
    }
}
