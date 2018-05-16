#include "library.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Library::Library(QObject *parent) :
    QObject(parent)
{

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
 * Getter for paths property.
 *
 * :return: paths
 */
QStringList Library::paths() const
{
    return m_paths;
}

/*
 * Loads library from multiple paths. Creates a
 * library builder thread and returns immediately.
 *
 * :param paths: paths
 */
void Library::load(const QStringList &paths)
{
    m_paths << paths;

    pm_audioLoader = new AudioLoader(m_paths, this);
    connect(pm_audioLoader, SIGNAL(finished()), this, SLOT(onAudioLoaderFinished()));
    connect(pm_audioLoader, SIGNAL(finished()), this, SIGNAL(loaded()));
    connect(pm_audioLoader, SIGNAL(audioLoaded(Audio*)), this, SLOT(insert(Audio*)));
    pm_audioLoader->start();
}

/*
 * Inserts audio into library. The audio list
 * will always be sorted by title when using
 * this method.
 *
 * :param audio: audio
 */
void Library::insert(Audio *audio)
{
    Audios::iterator iterator = std::lower_bound(m_audios.begin(), m_audios.end(), audio,
        [](const Audio *left, const Audio *right)
        {
            return QString::compare(left->title(), right->title(), Qt::CaseInsensitive) < 0;
        });
    int index = iterator - m_audios.begin();
    m_audios.insert(iterator, audio);
    emit AudioInserted(audio, index);
}

/*
 * Audio loader finished event. Starts the
 * cache builder.
 */
void Library::onAudioLoaderFinished()
{
    pm_cacheBuilder = new CacheBuilder(m_audios, this);
    pm_cacheBuilder->start();
}
