#include "dbaudio.hpp"

#include <QSqlRecord>

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

bool DbAudio::updatePrimaryKey(const File &file)
{
    query().prepare(
        "UPDATE audios SET"
        " file = :newfile,"
        "WHERE file = :file"
    );
    query().bindValue(":newfile", file);
    query().bindValue(":file", m_file);
    m_file = file;

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
