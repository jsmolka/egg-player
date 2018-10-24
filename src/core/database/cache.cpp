#include "cache.hpp"

#include <QDateTime>
#include <QFileInfo>

#include "core/database/dbaudio.hpp"
#include "core/database/dbcover.hpp"

Audio *Cache::loadAudio(const QString &file)
{    
    DbAudio dbAudio;
    if (dbAudio.getByFile(file))
    {
        Audio *audio = new Audio;
        dbAudio.assignTo(audio);
        audio->setValid(true);
        audio->setCached(true);
        audio->setOutdated(audio->modified() !=  QFileInfo(file).lastModified().toSecsSinceEpoch());
        return audio;
    }
    else
    {
        Audio *audio = new Audio(file);
        if (audio->isValid())
            return audio;
        else
            delete audio;
    }
    return nullptr;
}

bool Cache::insertAudio(Audio *audio)
{
    DbAudio dbAudio;
    dbAudio.loadFrom(audio);
    audio->setCached(true);

    return dbAudio.insert();
}

bool Cache::updateAudio(Audio *audio)
{
    DbAudio dbAudio;
    dbAudio.loadFrom(audio);
    audio->setCached(true);

    return dbAudio.commit();
}

bool Cache::updateAudioCover(Audio *audio, const QPixmap &cover)
{
    DbCover dbCover;
    if (!dbCover.getOrInsertCover(cover))
    {
        LOG("Could not get or insert cover %1", audio->file());
        return false;
    }
    return updateAudioCoverId(audio, dbCover.id());
}

bool Cache::updateAudioCoverId(Audio *audio, int coverId)
{
    DbAudio dbAudio;
    dbAudio.loadFrom(audio);
    audio->setCached(true);
    audio->cover().setId(coverId);

    return dbAudio.updateCoverId(coverId);
}
