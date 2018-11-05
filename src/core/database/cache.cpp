#include "cache.hpp"

#include <QDateTime>
#include <QFileInfo>

#include "core/database/dbaudio.hpp"
#include "core/database/dbcover.hpp"

Audio *Cache::loadAudio(const QString &file)
{    
    Audio *audio = loadAudioFromCache(file);
    if (audio)
        return audio;

    audio = new Audio(file);
    if (audio->isValid())
        return audio;

    delete audio;
    return nullptr;
}

bool Cache::insertAudio(Audio *audio)
{
    db::Audio dbAudio;
    dbAudio.loadFrom(audio);
    audio->setCached(true);

    return dbAudio.insert();
}

bool Cache::updateAudio(Audio *audio)
{
    db::Audio dbAudio;
    dbAudio.loadFrom(audio);
    audio->setCached(true);

    return dbAudio.commit();
}

bool Cache::updateAudioCover(Audio *audio, const QPixmap &cover)
{
    const int id = coverId(cover);
    if (id == 0)
        return false;

    return updateAudioCoverId(audio, id);
}

QPixmap Cache::loadCover(int id)
{
    db::Cover dbCover;
    dbCover.getById(id);

    return dbCover.cover();
}

Audio *Cache::loadAudioFromCache(const QString &file)
{
    db::Audio dbAudio;
    if (dbAudio.getByFile(file))
    {
        Audio *audio = new Audio;
        dbAudio.assignTo(audio);
        audio->setValid(true);
        audio->setCached(true);
        audio->setOutdated(audio->modified() !=  QFileInfo(file).lastModified().toSecsSinceEpoch());
        return audio;
    }
    return nullptr;
}

bool Cache::updateAudioCoverId(Audio *audio, int coverId)
{
    db::Audio dbAudio;
    dbAudio.loadFrom(audio);
    audio->setCached(true);
    audio->cover().setId(coverId);

    return dbAudio.updateCoverId(coverId);
}

int Cache::coverId(const QPixmap &cover)
{
    db::Cover dbCover;
    if (!dbCover.getOrInsertCover(cover))
        return 0;

    return dbCover.id();
}
