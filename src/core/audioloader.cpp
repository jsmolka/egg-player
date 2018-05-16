#include "audioloader.hpp"

/*
 * Constructor.
 *
 * param parent: parent, default nullptr
 */
AudioLoader::AudioLoader(QObject *parent) :
    QThread(parent)
{

}

/*
 * Constructor. Connects the thread to the app
 * so that it automatically aborts and deletes.
 *
 * :param paths: paths
 * :param parent: parent, default nullptr
 */
AudioLoader::AudioLoader(const QStringList &paths, QObject *parent) :
    QThread(parent),
    m_paths(paths)
{
    m_abort = false;

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(abort()));
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

/*
 * Destructor.
 */
AudioLoader::~AudioLoader()
{

}

/*
 * Sets the abort property and cleanly exits
 * the thread.
 */
void AudioLoader::abort()
{
    m_abort = true;
    quit();
    wait();
}

/*
 * Implemented run function. This is the main
 * function of the thread. Loads the library.
 */
void AudioLoader::run()
{
    for (const QString &path : m_paths)
    {
        if (Utils::exists(path))
            loadFromPath(path);
        else
            Logger::log("LibraryBuilder: Path does not exist '%1'", {path});
    }
}

/*
 * Loads audios from a path.
 *
 * :param path: path
 * :emit audioLoaded: loaded audio
 */
void AudioLoader::loadFromPath(const QString &path)
{
    QStringList files = Utils::glob(path, "mp3");
    if (files.isEmpty())
    {
        Logger::log("LibraryBuilder: Path contains no audio files '%1'", {path});
        return;
    }

    for (const QString &file : files)
    {
        if (m_abort)
            return;

        Audio *audio = new Audio(file);
        if (audio->isValid())
            emit audioLoaded(audio);
        else
            delete audio;

    }
}
