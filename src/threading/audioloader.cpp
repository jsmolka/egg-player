#include "audioloader.hpp"


AudioLoader::AudioLoader(QObject *parent)
    : AbstractThread(parent)
{

}

AudioLoader::AudioLoader(const QVector<QString> &files, QObject *parent)
    : AbstractThread(parent)
    , m_files(files)
{

}

AudioLoader::~AudioLoader()
{

}

void AudioLoader::setFiles(const QVector<QString> &files)
{
    m_files = files;
}

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
