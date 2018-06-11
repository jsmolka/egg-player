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
    Cache cache;
    for (const QString &file : m_files)
    {
        if (isAbort())
            return;

        Audio *audio = cache.load(file);
        if (!audio)
        {
            audio = new Audio(file);
            if (audio->isValid())
                cache.insertTags(audio);
        }

        if (audio->isValid())
            emit loaded(audio);
        else
            delete audio;
    }
}
