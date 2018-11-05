#include "dbaudio.hpp"

db::Audio::Audio()
    : m_year(0)
    , m_track(0)
    , m_duration(0)
    , m_coverId(0)
    , m_modified(0)
{

}

bool db::Audio::exists()
{
    query().prepare(
        "SELECT 1 FROM audios "
        "WHERE file = :file"
    );
    query().bindValue(":file", m_file);

    return query().exec() && query().first();
}

bool db::Audio::insert()
{
    query().prepare(
        "INSERT INTO audios VALUES ("
        "  :file,"
        "  :title,"
        "  :artist,"
        "  :album,"
        "  :genre,"
        "  :year,"
        "  :track,"
        "  :duration,"
        "  :coverid,"
        "  :modified"
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

bool db::Audio::commit()
{
    query().prepare(
        "UPDATE audios SET"
        "  title = :title,"
        "  artist = :artist,"
        "  album = :album,"
        "  genre = :genre,"
        "  year = :year,"
        "  track = :track,"
        "  duration = :duration,"
        "  coverid = :coverid,"
        "  modified = :modified "
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

bool db::Audio::createTable()
{
    return query().exec(
        "CREATE TABLE IF NOT EXISTS audios ("
        "  file TEXT PRIMARY KEY,"
        "  title TEXT,"
        "  artist TEXT,"
        "  album TEXT,"
        "  genre TEXT,"
        "  year INTEGER,"
        "  track INTEGER,"
        "  duration INTEGER,"
        "  coverid INTEGER,"
        "  modified INTEGER"
        ")"
    );
}

bool db::Audio::getByFile(const QString &file)
{
    return getBy("file", file);
}

bool db::Audio::getByTitle(const QString &title)
{
    return getBy("title", title);
}

bool db::Audio::getByAlbum(const QString &album)
{
    return getBy("album", album);
}

bool db::Audio::getByArtist(const QString &artist)
{
    return getBy("artist", artist);
}

bool db::Audio::getByYear(int year)
{
    return getBy("year", year);
}

bool db::Audio::getByDuration(int duration)
{
    return getBy("duration", duration);
}

bool db::Audio::getByCoverId(int coverId)
{
    return getBy("coverid", coverId);
}

bool db::Audio::getByModified(qint64 modified)
{
    return getBy("modified", modified);
}

bool db::Audio::updateFile(const QString &file)
{
    query().prepare(
        "UPDATE audios SET"
        "  file = :newfile, "
        "WHERE file = :file"
    );
    query().bindValue(":file", m_file);
    query().bindValue(":newfile", file);

    m_file = file;

    return query().exec();
}

bool db::Audio::updateTitle(const QString &title)
{
    m_title = title;

    return update("title", title);
}

bool db::Audio::updateAlbum(const QString &album)
{
    m_album = album;

    return update("album", album);
}

bool db::Audio::updateArtist(const QString &artist)
{
    m_artist = artist;

    return update("artist", artist);
}

bool db::Audio::updateYear(int year)
{
    m_year = year;

    return update("year", year);
}

bool db::Audio::updateDuration(int duration)
{
    m_duration = duration;

    return update("duration", duration);
}

bool db::Audio::updateCoverId(int coverId)
{
    m_coverId = coverId;

    return update("coverid", coverId);
}

bool db::Audio::updateModified(qint64 modified)
{
    m_modified = modified;

    return update("modified", modified);
}

void db::Audio::assignTo(::Audio *audio)
{
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
}

void db::Audio::loadFrom(::Audio *audio)
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

bool db::Audio::getBy(const QString &column, const QVariant &value)
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

bool db::Audio::update(const QString &column, const QVariant &value)
{
    query().prepare(
        "UPDATE audios SET"
        "  " + column + " = :value "
        "WHERE file = :file"
    );
    query().bindValue(":file", m_file);
    query().bindValue(":column", column);
    query().bindValue(":value", value);

    return query().exec();
}

void db::Audio::loadFromRecord(const QSqlRecord &record)
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
