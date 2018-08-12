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
    connect(&m_audioLoader, &AudioLoaderController::loaded, this, &Library::insert);
    connect(&m_audioLoader, &AudioLoaderController::finished,this, &Library::onAudioLoaderFinished);

    connect(&m_watcher, &FileSystemWatcher::added, this, &Library::onWatcherAdded);
    connect(&m_watcher, &FileSystemWatcher::removed, this, &Library::onWatcherRemoved);
    connect(&m_watcher, &FileSystemWatcher::modified, this, &Library::onWatcherModified);
    connect(&m_watcher, &FileSystemWatcher::renamed, this, &Library::onWatcherRenamed);
}

Library::~Library()
{

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
    for (const QString &path : paths)
    {
        m_watcher.watchDir(path);
    }

    m_audioLoader.setFiles(globFiles(paths));
    m_audioLoader.start();
}

void Library::insert(Audio *audio)
{
    int index = m_sorted ? insertBinary(audio) : insertLinear(audio);
    m_watcher.watchAudio(audio);
    emit inserted(audio, index);
}

void Library::onAudioLoaderFinished()
{
    m_coverLoader.setAudios(m_audios.vector());
    m_coverLoader.start();
}

void Library::onWatcherAdded(const QString &file)
{
    m_audioLoader.setFiles(Files() << file);
    m_audioLoader.start();
}

void Library::onWatcherRemoved(Audio *audio)
{
    int index = m_audios.indexOf(audio);
    m_audios.remove(index);
}

void Library::onWatcherModified(Audio *audio)
{
    m_audioUpdater.setAudio(audio);
    m_audioUpdater.start();
}

void Library::onWatcherRenamed(Audio *audio, const QString &file)
{
    Cache().updateAudio(audio, file);
    audio->setPath(file);
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
