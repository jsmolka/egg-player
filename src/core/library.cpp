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
        delete m_audios.takeAt(0);
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

Audios * Library::audios()
{
    return &m_audios;
}

CoverLoaderController * Library::coverLoader()
{
    return &m_coverLoader;
}

AudioLoaderController * Library::audioLoader()
{
    return &m_audioLoader;
}

void Library::load(const Paths &paths)
{
    m_audioLoader.setFiles(globFiles(paths));
    m_audioLoader.start();
}

void Library::insert(Audio *audio)
{
    int index = m_sorted ? insertBinary(audio) : insertLinear(audio);
    emit inserted(audio, index);
}

void Library::onAudioLoaderFinished()
{
    m_coverLoader.setAudios(m_audios.vector());
    m_coverLoader.start();
}

int Library::lowerBound(Audio *audio)
{
    int low = 0;
    int high = m_audios.size();
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (*audio < *m_audios.at(mid))
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

int Library::insertLinear(Audio *audio)
{
    m_audios << audio;
    return -1;
}

Files Library::globFiles(const Paths &paths)
{
    Files files;
    for (const QString &path : paths)
    {
        if (!m_loaded.contains(path))
        {
            m_loaded.insert(path);
            files << FileUtil::glob(path, "*.mp3");
        }
    }
    return files;
}
