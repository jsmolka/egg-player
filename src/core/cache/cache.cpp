#include "cache.hpp"

#include <QDateTime>
#include <QFileInfo>
#include <QMutex>
#include <QMutexLocker>

#include "constants.hpp"
#include "logger.hpp"

void Cache::initialize()
{
    createCovers();
    createAudios();
    insertDefaultCover();
}

Audio *Cache::loadAudio(const File &file)
{
    query().prepare(
        "SELECT * FROM audios "
        "WHERE file = :file"
    );
    query().bindValue(":file", file);
    query().exec();

    Audio *audio = nullptr;
    if (query().first())
    {
        audio = new Audio;
        audio->setValid(true);
        audio->setCached(true);
        audio->setFile(query().value(0).toString());
        audio->tag().setTitle(query().value(1).toString());
        audio->tag().setArtist(query().value(2).toString());
        audio->tag().setAlbum(query().value(3).toString());
        audio->tag().setGenre(query().value(4).toString());
        audio->tag().setYear(query().value(5).toInt());
        audio->tag().setTrack(query().value(6).toInt());
        audio->tag().setDuration(query().value(7).toInt());
        audio->duration().setSecs(query().value(7).toInt());
        audio->cover().setId(query().value(8).toInt());
        audio->setModified(query().value(9).toInt());
        audio->setOutdated(audio->modified() != QFileInfo(audio->file()).lastModified().toSecsSinceEpoch());
    }
    return audio;
}

void Cache::insertAudio(Audio *audio)
{
    query().prepare(
        "INSERT INTO audios VALUES ("
        " :file,"
        " :title,"
        " :artist,"
        " :album,"
        " :genre,"
        " :year,"
        " :track,"
        " :duration,"
        " :coverid,"
        " :modified"
        ")"
    );
    query().bindValue(":file", audio->file());
    query().bindValue(":title", audio->tag().title());
    query().bindValue(":artist", audio->tag().artist());
    query().bindValue(":album", audio->tag().album());
    query().bindValue(":genre", audio->tag().genre());
    query().bindValue(":year", audio->tag().year());
    query().bindValue(":track", audio->tag().track());
    query().bindValue(":duration", audio->duration().secs());
    query().bindValue(":coverid", audio->cover().id());
    query().bindValue(":modified", audio->modified());
    query().exec();

    audio->setCached(true);
}

void Cache::updateAudio(Audio *audio, const File &newFile)
{
    query().prepare(
        "UPDATE audios SET"
        " file = :newFile,"
        " title = :title,"
        " artist = :artist,"
        " album = :album,"
        " genre = :genre,"
        " year = :year,"
        " track = :track,"
        " duration = :duration,"
        " coverid = :coverid,"
        " modified = :modified "
        "WHERE file = :file"
    );
    query().bindValue(":newFile", newFile.isNull() ? audio->file() : newFile);
    query().bindValue(":title", audio->tag().title());
    query().bindValue(":artist", audio->tag().artist());
    query().bindValue(":album", audio->tag().album());
    query().bindValue(":genre", audio->tag().genre());
    query().bindValue(":year", audio->tag().year());
    query().bindValue(":track", audio->tag().track());
    query().bindValue(":duration", audio->duration().secs());
    query().bindValue(":coverid", audio->cover().id());
    query().bindValue(":modified", audio->modified());
    query().bindValue(":file", audio->file());
    query().exec();
}

int Cache::insertCover(const QPixmap &cover)
{
    const QByteArray bytes = coverToBytes(cover);
    int id = coverId(bytes);
    if (id == 0)
        id = insertByteCover(bytes);

    return id;
}

void Cache::updateCover(const QPixmap &cover)
{
    const QByteArray bytes = coverToBytes(cover);
    const int id = coverId(bytes);
    if (id > 0)
        updateByteCover(id, bytes);
}

void Cache::setAudioCoverId(Audio *audio, int id)
{
    query().prepare(
        "UPDATE audios SET"
        " coverid = :coverid "
        "WHERE file = :file"
    );
    query().bindValue(":file", audio->file());
    query().bindValue(":coverid", id);
    query().exec();

    audio->cover().setId(id);
}

void Cache::updateAudioCover(Audio *audio, const QPixmap &cover)
{
    const int id = insertCover(cover);
    if (id > 0)
        setAudioCoverId(audio, id);
}

QPixmap Cache::coverById(int id)
{
    query().prepare(
        "SELECT cover FROM covers "
        "WHERE id = :id"
    );
    query().bindValue(":id", id);
    query().exec();

    QPixmap cover;
    if (query().first())
    {
        const QByteArray bytes = query().value(0).toByteArray();
        cover.loadFromData(bytes);
    }
    return cover;
}

QByteArray Cache::coverToBytes(const QPixmap &cover)
{
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    cover.save(&buffer, "PNG");

    return bytes;
}

void Cache::createCovers()
{
    query().exec(
        "CREATE TABLE IF NOT EXISTS covers("
        " id INTEGER PRIMARY KEY,"
        " size INTEGER,"
        " cover BLOB"
        ")"
    );
}

void Cache::createAudios()
{
    query().exec(
        "CREATE TABLE IF NOT EXISTS audios("
        " file TEXT PRIMARY KEY,"
        " title TEXT,"
        " artist TEXT,"
        " album TEXT,"
        " genre TEXT,"
        " year INTEGER,"
        " track INTEGER,"
        " duration INTEGER,"
        " coverid INTEGER,"
        " modified INTEGER"
        ")"
    );
}

bool Cache::defaultCoverExists()
{
    query().exec(
        "SELECT 1 FROM covers "
        "WHERE id = 1"
    );
    return query().first();
}

void Cache::insertDefaultCover()
{
    if (defaultCoverExists())
        return;

    const QPixmap cover = Cover::scale(QPixmap(IMG_DEFAULT_COVER), Cover::defaultSize());
    const QByteArray bytes = coverToBytes(cover);

    query().prepare(
        "INSERT INTO covers VALUES ("
        " :id,"
        " :size,"
        " :cover"
        ")"
    );
    query().bindValue(":id", 1);
    query().bindValue(":size", bytes.size());
    query().bindValue(":cover", bytes);
    query().exec();
}

int Cache::insertByteCover(const QByteArray &bytes)
{
    static QMutex mutex;
    const QMutexLocker locker(&mutex);
    const int id = lastCoverId() + 1;

    query().prepare(
        "INSERT INTO covers VALUES ("
        " :id,"
        " :size,"
        " :cover"
        ")"
    );
    query().bindValue(":id", id);
    query().bindValue(":size", bytes.size());
    query().bindValue(":cover", bytes);
    return query().exec() ? id : 0;
}

void Cache::updateByteCover(int id, const QByteArray &bytes)
{
    query().prepare(
        "UPDATE covers SET"
        " cover = :cover "
        "WHERE id = :id"
    );
    query().bindValue(":cover", bytes);
    query().bindValue(":id", id);
    query().exec();
}

int Cache::coverId(const QByteArray &bytes)
{
    int id = coverIdBySize(bytes.size());
    if (id == 0)
        id = coverIdByBlob(bytes);

    return id;
}

int Cache::lastCoverId()
{
    query().exec("SELECT max(id) FROM covers");

    int id = 1;
    if (query().first())
        id = query().value(0).toInt();

    return id;
}

int Cache::coverIdBySize(int size)
{
    query().prepare(
        "SELECT id FROM covers "
        "WHERE size = :size"
    );
    query().bindValue(":size", size);
    query().exec();

    int id = 0;
    if (query().first())
        id = query().value(0).toInt();
    if (query().next())
        id = 0;

    return id;
}

int Cache::coverIdByBlob(const QByteArray &bytes)
{
    query().prepare(
        "SELECT id FROM covers "
        "WHERE cover = :cover"
    );
    query().bindValue(":cover", bytes);
    query().exec();

    int id = 0;
    if (query().first())
        id = query().value(0).toInt();

    return id;
}
