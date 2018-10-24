#include "audioloader.hpp"

#include <QApplication>

#include "cache.hpp"

AudioLoader::AudioLoader(QObject *parent)
    : Callable(parent)
{

}

void AudioLoader::load(const File &file)
{
    Audio *audio = Cache::loadAudio(file);
    if (!audio)
        return;

    if (!audio->isCached())
    {
        if (isInterrupted())
            return;

        Cache::insertAudio(audio);
    }
    if (audio->isOutdated())
    {
        if (isInterrupted())
            return;

        audio->update();
        audio->cover().invalidate();
        Cache::updateAudio(audio);
    }
    if (!audio->cover().isValid())
    {
        if (isInterrupted())
            return;

        const QPixmap cover = Cover::loadFromFile(audio->file());
        if (!cover.isNull())
            Cache::updateAudioCover(audio, cover);
    }
    audio->moveToThread(qApp->thread());
    emit loaded(audio);
}
