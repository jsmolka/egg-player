#include "audioloader.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
AudioLoader::AudioLoader(QObject *parent) :
    AbstractThread(parent)
{

}

/*
 * Constructor.
 *
 * :param files: files
 * :param parent: parent, default nullptr
 */
AudioLoader::AudioLoader(const StringList &files, QObject *parent) :
    AbstractThread(parent),
    m_files(files)
{

}

/*
 * Destructor.
 */
AudioLoader::~AudioLoader()
{

}

/*
 * Setter for files property.
 *
 * :param files: files
 */
void AudioLoader::setFiles(const StringList &files)
{
    m_files = files;
}

/*
 * Loads audios.
 */
void AudioLoader::run()
{
    for (const QString &file : m_files)
    {
        if (isAbort())
            return;

        Audio *audio = new Audio(file);
        if (audio->isValid())
            emit loaded(audio);
        else
            delete audio;
    }
}
