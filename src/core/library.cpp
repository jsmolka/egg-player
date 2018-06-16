#include "library.hpp"

Library::Library(QObject *parent)
    : QObject(parent)
    , m_sorted(false)
    , pm_audioLoader(new AudioLoader(this))
    , pm_cacheBuilder(new CacheBuilder(this))
{
    connect(pm_audioLoader, SIGNAL(loaded(Audio *)), this, SLOT(insert(Audio *)));
    connect(pm_audioLoader, SIGNAL(finished()), this, SLOT(onAudioLoaderFinished()));
    connect(pm_audioLoader, SIGNAL(finished()), this, SIGNAL(loaded()));
}

Library::Library(bool sorted, QObject *parent)
    : Library(parent)
{
    m_sorted = sorted;
}

Library::~Library()
{
    while (!m_audios.isEmpty())
        delete m_audios.takeFirst();
}

Library * Library::instance()
{
    if (!_instance)
        _instance = new Library(true, qApp);

    return _instance;
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

void Library::load(const StringList &paths)
{
    pm_audioLoader->setFiles(uniqueFiles(paths));
    pm_audioLoader->start();
}

void Library::insert(Audio *audio)
{
    if (m_sorted)
        insertBinary(audio);
    else
        append(audio);
}

void Library::onAudioLoaderFinished()
{
    pm_cacheBuilder->setAudios(m_audios);
    pm_cacheBuilder->start();
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

void Library::insertBinary(Audio *audio)
{
    int index = lowerBound(audio);
    m_audios.insert(index, audio);
    emit inserted(audio, index);
}

void Library::append(Audio *audio)
{
    m_audios << audio;
    emit inserted(audio, -1);
}

StringList Library::uniqueFiles(const StringList &paths)
{
    StringList files;
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

Library * Library::_instance = nullptr;
