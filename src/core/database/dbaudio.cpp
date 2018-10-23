#include "dbaudio.hpp"

#include <QDateTime>
#include <QFileInfo>
#include <QSqlRecord>

bool DbAudio::exists()
{
    query().prepare(
        "SELECT 1 FROM audios "
        "WHERE file = :file"
    );
    query().bindValue(":file", m_file);

    return query().exec() && query().first();
}

bool DbAudio::insert()
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
    query().bindValue(":file", m_file);
    query().bindValue(":title", m_title);
    query().bindValue(":artist", m_artist);
    query().bindValue(":album", m_album);
    query().bindValue(":genre", m_genre);
    query().bindValue(":year", m_year);
    query().bindValue(":track", m_track);
    query().bindValue(":duration", m_duration);
    query().bindValue(":coverid", m_coverId);
    query().bindValue(":modified", m_modified);

    return query().exec();
}

bool DbAudio::commit()
{
    query().prepare(
        "UPDATE audios SET"
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
    query().bindValue(":file", m_file);
    query().bindValue(":title", m_title);
    query().bindValue(":artist", m_artist);
    query().bindValue(":album", m_album);
    query().bindValue(":genre", m_genre);
    query().bindValue(":year", m_year);
    query().bindValue(":track", m_track);
    query().bindValue(":duration", m_duration);
    query().bindValue(":coverid", m_coverId);
    query().bindValue(":modified", m_modified);

    return query().exec();
}

bool DbAudio::updatePrimaryKey(const QString &file)
{
    query().prepare(
        "UPDATE audios SET"
        " file = :newfile, "
        "WHERE file = :file"
    );
    query().bindValue(":newfile", file);
    query().bindValue(":file", m_file);

    m_file = file;

    return query().exec();
}

bool DbAudio::getByFile(const QString &file)
{
    return getBy("file", file);
}

bool DbAudio::getByTitle(const QString &title)
{
    return getBy("title", title);
}

bool DbAudio::getByAlbum(const QString &album)
{
    return getBy("album", album);
}

bool DbAudio::getByArtist(const QString &artist)
{
    return getBy("artist", artist);
}

bool DbAudio::getByYear(int year)
{
    return getBy("year", year);
}

bool DbAudio::getByDuration(int duration)
{
    return getBy("duration", duration);
}

bool DbAudio::getByCoverId(int coverId)
{
    return getBy("coverid", coverId);
}

bool DbAudio::getByModified(qint64 modified)
{
    return getBy("modified", modified);
}

void DbAudio::assignTo(Audio *audio)
{
    audio->setValid(true);
    audio->setCached(true);
    audio->setFile(m_file);
    audio->tag().setTitle(m_title);
    audio->tag().setArtist(m_artist);
    audio->tag().setAlbum(m_album);
    audio->tag().setGenre(m_genre);
    audio->tag().setYear(m_year);
    audio->tag().setTrack(m_track);
    audio->duration().setSecs(m_duration);
    audio->cover().setId(m_coverId);
    audio->setModified(m_modified);
    audio->setOutdated(m_modified !=  QFileInfo(m_file).lastModified().toSecsSinceEpoch());
}

void DbAudio::loadFrom(Audio *audio)
{
    m_file = audio->file();
    m_title = audio->tag().title();
    m_artist = audio->tag().artist();
    m_album = audio->tag().album();
    m_genre = audio->tag().genre();
    m_year = audio->tag().year();
    m_track = audio->tag().track();
    m_duration = audio->duration().secs();
    m_coverId = audio->cover().id();
    m_modified = audio->modified();
}

bool DbAudio::getBy(const QString &column, const QVariant &value)
{
    query().prepare(
        "SELECT * FROM audios "
        "WHERE " + column + " = :value"
    );
    query().bindValue(":value", value);

    if (!query().exec())
        return false;

    if (!query().first())
        return false;

    loadFromRecord(query().record());

    return true;
}

void DbAudio::loadFromRecord(const QSqlRecord &record)
{
    m_file = record.value("file").toString();
    m_title = record.value("title").toString();
    m_artist = record.value("artist").toString();
    m_album = record.value("album").toString();
    m_genre = record.value("genre").toString();
    m_year = record.value("year").toInt();
    m_track = record.value("track").toInt();
    m_duration = record.value("duration").toInt();
    m_coverId = record.value("coverid").toInt();
    m_modified = static_cast<qint64>(record.value("modified").toULongLong());
}
