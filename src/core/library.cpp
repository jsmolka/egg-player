#include "library.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
Library::Library(QObject *parent) :
    QObject(parent),
    pm_cacheBuilder(new CacheBuilder(this)),
    pm_audioLoader(new AudioLoader(this))
{
    connect(pm_audioLoader, SIGNAL(finished()), this, SLOT(onAudioLoaderFinished()));
    connect(pm_audioLoader, SIGNAL(finished()), this, SIGNAL(loaded()));
    connect(pm_audioLoader, SIGNAL(loaded(Audio*)), this, SLOT(insert(Audio*)));
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
 * Loads the library by creating an audio
 * builder. This function should not be called
 * multiple times for the same paths.
 *
 * :param paths: paths
 */
void Library::load(const QStringList &paths)
{
    pm_audioLoader->setPaths(paths);
    pm_audioLoader->start();
}

/*
 * Inserts an audio into the library. The audio
 * list will always be sorted by title when
 * using this method.
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
    emit inserted(audio, index);
}

/*
 * Starts the cache builder.
 */
void Library::onAudioLoaderFinished()
{
    pm_cacheBuilder->setAudios(m_audios);
    pm_cacheBuilder->start();
}
