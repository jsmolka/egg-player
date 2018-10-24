#include "audioloader.hpp"

#include <QApplication>

#include "core/cover.hpp"
#include "core/database/cache.hpp"

void AudioLoader::load(const QString &file)
{
    Audio *audio = Cache::loadAudio(file);
    if (!audio)
        return;

    if (!insertAudio(audio))
        return;

    if (!updateAudio(audio))
        return;

    if (!loadCover(audio))
        return;

    audio->moveToThread(qApp->thread());
    emit loaded(audio);
}

bool AudioLoader::insertAudio(Audio *audio)
{
    if (isInterrupted())
        return false;

    if (!audio->isCached())
        Cache::insertAudio(audio);

    return true;
}

bool AudioLoader::updateAudio(Audio *audio)
{
    if (isInterrupted())
        return false;

    if (audio->isOutdated())
    {
        if (!audio->update())
            return false;

        audio->cover().invalidate();
        Cache::updateAudio(audio);
    }
    return true;
}

bool AudioLoader::loadCover(Audio *audio)
{
    if (isInterrupted())
        return false;

    if (!audio->cover().isValid())
    {
        const QPixmap cover = Cover::loadFromFile(audio->file());
        if (!cover.isNull())
            Cache::updateAudioCover(audio, cover);
    }
    return true;
}
