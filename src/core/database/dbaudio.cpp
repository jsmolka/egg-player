#include "dbaudio.hpp"

#include <QSqlRecord>

void DbAudio::setFile(const File &file)
{
    m_file = file;
}

File DbAudio::file() const
{
    return m_file;
}

void DbAudio::setTitle(const QString &title)
{
    m_title = title;
}

QString DbAudio::title() const
{
    return m_title;
}

void DbAudio::setArtist(const QString &artist)
{
    m_artist = artist;
}

QString DbAudio::artist() const
{
    return m_artist;
}

void DbAudio::setAlbum(const QString &album)
{
    m_album = album;
}

QString DbAudio::album() const
{
    return m_album;
}

void DbAudio::setGenre(const QString &genre)
{
    m_genre = genre;
}

QString DbAudio::genre() const
{
    return m_genre;
}

void DbAudio::setYear(int year)
{
    m_year = year;
}

int DbAudio::year() const
{
    return m_year;
}

void DbAudio::setTrack(int track)
{
    m_track = track;
}

int DbAudio::track() const
{
    return m_track;
}

void DbAudio::setDuration(int duration)
{
    m_duration = duration;
}

int DbAudio::duration() const
{
    return m_duration;
}

void DbAudio::setCoverId(int id)
{
    m_coverId = id;
}

int DbAudio::coverId() const
{
    return m_coverId;
}

void DbAudio::setModified(qint64 modified)
{
    m_modified = modified;
}

qint64 DbAudio::modified() const
{
    return m_modified;
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

bool DbAudio::getBy(const QVariant &column, const QVariant &value)
{
    query().prepare(
        "SELECT * FROM audios "
        "WHERE :column = :value"
    );
    query().bindValue(":column", column);
    query().bindValue(":value", value);

    if (!query().exec())
        return false;

    if (!query().first())
        return false;

    const QSqlRecord record = query().record();
    m_file = record.value("file").toString();
    m_title = record.value("title").toString();
    m_artist = record.value("artist").toString();
    m_album = record.value("album").toString();
    m_genre = record.value("genre").toString();
    m_year = record.value("year").toInt();
    m_track = record.value("track").toInt();
    m_duration = record.value("duration").toInt();
    m_coverId = record.value("coverid").toInt();
    m_modified = record.value("modified").toInt();

    return true;
}

bool DbAudio::getByFile(const File &file)
{
    return getBy("file", file);
}

bool DbAudio::getByTitle(const QString &title)
{
    return getBy("title", title);
}
