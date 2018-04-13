#include "library.hpp"

Library::Library()
{

}

Library::Library(const QString &path)
{
    loadFiles(path);
}

Library::~Library()
{
    for (Audio *audio : m_audioList)
        delete audio;
}

AudioList Library::audioList() const
{
    return m_audioList;
}

bool Library::isEmpty() const
{
    return m_audioList.isEmpty();
}

AudioList Library::search(const QString &string, Qt::CaseSensitivity cs)
{
    AudioList result;
    for (Audio *audio : m_audioList)
        if (audio->title().contains(string, cs) ||
                audio->artist().contains(string, cs) ||
                audio->album().contains(string, cs))
            result << audio;
    return result;
}

void Library::sortByTitle()
{
    m_audioList.sortByTitle();
}

Audio * Library::audioAt(int idx)
{
    return m_audioList[idx];
}

void Library::loadFiles(const QString &path)
{
    Cache cache;
    cache.connect();

    QStringList files = FileUtil::glob(path, "*.mp3");
    if (!files.isEmpty())
    {
        for (const QString &file : files)
        {
            Audio *audio = new Audio(file);
            if (audio->isValid())
            {
                if (!cache.exists(audio))
                    cache.insert(audio);

                m_audioList << audio;
            }
        }
    }
    cache.close();
}
