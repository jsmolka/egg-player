#include "library.hpp"

Library::Library(QObject *parent)
    : Library(false, parent)
{

}

Library::Library(bool sorted, QObject *parent)
    : QObject(parent)
    , m_sorted(sorted)
    , m_audioLoader(this)
    , m_coverLoader(this)
{
    connect(&m_audioLoader, &AudioLoaderController::loaded, this, &Library::insert);
    connect(&m_audioLoader, &AudioLoaderController::finished,this, &Library::onAudioLoaderFinished);

}

Library::~Library()
{
    while (!m_audios.isEmpty())
        delete m_audios.takeFirst();
}

Library * Library::instance()
{
    static Library *library = new Library(qApp);
    return library;
}

void Library::setSorted(bool sorted)
{
    m_sorted = sorted;
}

bool Library::isSorted() const
{
    return m_sorted;
}

Audios Library::audios() const
{
    return m_audios;
}

CoverLoaderController * Library::coverLoader()
{
    return &m_coverLoader;
}

AudioLoaderController * Library::audioLoader()
{
    return &m_audioLoader;
}

void Library::load(const Files &paths)
{
    m_audioLoader.setFiles(uniqueFiles(paths));
    m_audioLoader.start();
}

void Library::insert(Audio *audio)
{
    int index = m_sorted ? insertBinary(audio) : append(audio);
    emit inserted(audio, index);
}

void Library::onAudioLoaderFinished()
{
    m_coverLoader.setAudios(m_audios);
    m_coverLoader.start();
}

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

int Library::insertBinary(Audio *audio)
{
    int index = lowerBound(audio);
    m_audios.insert(index, audio);
    return index;
}

int Library::append(Audio *audio)
{
    m_audios << audio;
    return -1;
}

Files Library::uniqueFiles(const Files &paths)
{
    Files files;
    for (const QString &path : paths)
    {
        if (!m_paths.contains(path))
        {
            files << FileUtil::glob(path, "mp3");
            m_paths << path;
        }
        else
        {
            log("Library: Path has already been loaded %1", {path});
        }
    }
    return files;
}
