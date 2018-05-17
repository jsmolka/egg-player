#include "audioloader.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
AudioLoader::AudioLoader(QObject *parent) :
    QThread(parent),
    m_abort(false)
{
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(abort()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

/*
 * Constructor.
 *
 * :param paths: paths
 * :param parent: parent, default nullptr
 */
AudioLoader::AudioLoader(const QStringList &paths, QObject *parent) :
    AudioLoader(parent)
{
    m_paths = paths;
}

/*
 * Destructor.
 */
AudioLoader::~AudioLoader()
{

}

/*
 * Setter for paths property.
 *
 * :param paths: paths
 */
void AudioLoader::setPaths(const QStringList &paths)
{
    m_paths = paths;
}

/*
 * Exits the thread cleanly.
 */
void AudioLoader::abort()
{
    m_abort = true;
    quit();
    wait();
}

/*
 * Loads audios from paths.
 */
void AudioLoader::run()
{
    for (const QString &path : m_paths)
    {
        if (m_abort)
            return;

        if (Utils::exists(path))
            load(path);
        else
            Logger::log("AudioLoader: Path does not exist %1", {path});
    }
}

/*
 * Loads audios from a path.
 *
 * :param path: path
 * :emit loaded: audio
 */
void AudioLoader::load(const QString &path)
{
    QStringList files = Utils::glob(path, "mp3");
    if (files.isEmpty())
        Logger::log("AudioLoader: Path contains no files %1", {path});

    for (const QString &file : files)
    {
        if (m_abort)
            return;

        Audio *audio = new Audio(file);
        if (audio->isValid())
            emit loaded(audio);
        else
            delete audio;
    }
}
