#include "library.hpp"

Library::Library(QObject *parent)
    : Library(false, parent)
{

}

Library::Library(bool sorted, QObject *parent)
    : QObject(parent)
    , m_sorted(sorted)
    , m_audios(this)
    , m_watcher(this)
    , m_audioLoader(this)
    , m_audioUpdater(this)
    , m_coverLoader(this)
{
    connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, &Library::onFileChanged);

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

Audios * Library::audios()
{
    return &m_audios;
}

AudioLoaderController * Library::audioLoader()
{
    return &m_audioLoader;
}

AudioUpdaterController * Library::audioUpdater()
{
    return &m_audioUpdater;
}

CoverLoaderController * Library::coverLoader()
{
    return &m_coverLoader;
}

void Library::load(const Paths &paths)
{
    m_audioLoader.setFiles(globFiles(paths));
    m_audioLoader.start();
}

void Library::insert(Audio *audio)
{
    int index = m_sorted ? insertBinary(audio) : insertLinear(audio);
    m_watcher.addPath(audio->path());
    emit inserted(audio, index);
}

void Library::onAudioLoaderFinished()
{
    m_coverLoader.setAudios(m_audios.vector());
    m_coverLoader.start();
}

void Library::onFileChanged(const QString &file)
{
    if (FileUtil::exists(file))
        fileUpdated(file);
    else
        fileRemoved(file);
}

void Library::fileRemoved(const QString &file)
{
    for (auto iter = m_audios.begin(); iter != m_audios.end(); ++iter)
    {
        if (**iter == file)
        {
            m_audios.erase(iter);
            break;
        }
    }
}

void Library::fileUpdated(const QString &file)
{
    for (Audio *audio : m_audios)
    {
        if (*audio == file)
        {
            m_audioUpdater.setAudio(audio);
            m_audioUpdater.start();
            break;
        }
    }
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
