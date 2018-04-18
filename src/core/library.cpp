#include "library.hpp"

Library::Library(const QString &path)
{
    loadFiles(path);
}

Library::~Library()
{
    for (Audio *audio : m_audioList)
        if (audio)
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
    Logger::log(QString("FileUtil globbed %1 files").arg(files.size()));
    if (!files.isEmpty())
    {
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
    }
    Logger::log(QString("Library contains %1 audios").arg(m_audioList.size()));
    cache.close();
}
