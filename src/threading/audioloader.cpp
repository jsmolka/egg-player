#include "audioloader.hpp"

#include <QApplication>

AudioLoader::AudioLoader(QObject *parent)
    : Callable(parent)
{

}

void AudioLoader::load(const File &file)
{
    Audio *audio = m_cache.loadAudio(file);
    if (!audio)
        audio = new Audio(file);

    if (!audio->isValid())
        delete audio;
    if (!audio->isCached())
    {
        if (isInterrupted())
            return;

        m_cache.insertAudio(audio);
    }
    if (audio->isOutdated())
    {
        if (isInterrupted())
            return;

        audio->update();
        audio->cover().invalidate();
        m_cache.updateAudio(audio);
    }
    if (!audio->cover().isValid())
    {
        if (isInterrupted())
            return;

        const QPixmap cover = Cover::loadFromFile(audio->wideFile());
        m_cache.updateAudioCover(audio, cover);
    }
    audio->moveToThread(qApp->thread());
    emit loaded(audio);
}
