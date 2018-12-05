#include "cache.hpp"

#include <QDateTime>
#include <QFileInfo>

#include "core/database/audioitem.hpp"
#include "core/database/coveritem.hpp"

Audio Cache::loadAudio(const QString &file)
{    
    db::AudioItem audioItem;
    if (audioItem.getByFile(file))
    {
        Audio audio;
        audioItem.assignTo(audio);
        audio.setValid(true);
        audio.setCached(true);
        audio.setOutdated(audio.modified() != QFileInfo(file).lastModified().toSecsSinceEpoch());

        return audio;
    }
    return Audio(file);
}

bool Cache::insertAudio(Audio &audio)
{
    db::AudioItem audioItem;
    audioItem.loadFrom(audio);
    audio.setCached(true);

    return audioItem.insert();
}

bool Cache::updateAudio(Audio &audio)
{
    db::AudioItem audioItem;
    audioItem.loadFrom(audio);
    audio.setCached(true);

    return audioItem.commit();
}

bool Cache::updateAudioCover(Audio &audio, const QPixmap &cover)
{
    const int id = coverId(cover);
    if (id == 0)
        return false;

    return updateAudioCoverId(audio, id);
}

QPixmap Cache::loadCover(int id)
{
    db::CoverItem coverItem;
    coverItem.getById(id);

    return coverItem.cover();
}

int Cache::coverId(const QPixmap &cover)
{
    db::CoverItem coverItem;
    if (!coverItem.getOrInsertCover(cover))
        return 0;

    return coverItem.id();
}

bool Cache::updateAudioCoverId(Audio &audio, int coverId)
{
    db::AudioItem audioItem;
    audioItem.loadFrom(audio);
    audio.setCached(true);
    audio.cover().setId(coverId);

    return audioItem.updateCoverId(coverId);
}
