#include "audioitem.hpp"

db::AudioItem::AudioItem()
    : m_year(0)
    , m_track(0)
    , m_duration(0)
    , m_coverId(0)
    , m_modified(0)
{

}

bool db::AudioItem::exists()
{
    query().prepare(
        "SELECT 1 FROM audios "
        "WHERE file = :file"
    );
    query().bindValue(":file", m_file);

    return query().exec() && query().first();
}

bool db::AudioItem::insert()
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

bool db::AudioItem::commit()
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

bool db::AudioItem::createTable()
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

bool db::AudioItem::getByFile(const QString &file)
{
    return getBy("file", file);
}

bool db::AudioItem::getByTitle(const QString &title)
{
    return getBy("title", title);
}

bool db::AudioItem::getByAlbum(const QString &album)
{
    return getBy("album", album);
}

bool db::AudioItem::getByArtist(const QString &artist)
{
    return getBy("artist", artist);
}

bool db::AudioItem::getByYear(int year)
{
    return getBy("year", year);
}

bool db::AudioItem::getByDuration(int duration)
{
    return getBy("duration", duration);
}

bool db::AudioItem::getByCoverId(int coverId)
{
    return getBy("coverid", coverId);
}

bool db::AudioItem::getByModified(qint64 modified)
{
    return getBy("modified", modified);
}

bool db::AudioItem::updateFile(const QString &file)
{
    query().prepare(
        "UPDATE audios SET"
        "  file = :newfile "
        "WHERE file = :file"
    );
    query().bindValue(":file", m_file);
    query().bindValue(":newfile", file);

    if (query().exec())
    {
        m_file = file;
        return true;
    }
    return false;
}

bool db::AudioItem::updateTitle(const QString &title)
{
    return updateWrapper<QString>("title", title, m_title);
}

bool db::AudioItem::updateAlbum(const QString &album)
{
    return updateWrapper<QString>("album", album, m_album);
}

bool db::AudioItem::updateArtist(const QString &artist)
{
    return updateWrapper<QString>("artist", artist, m_artist);
}

bool db::AudioItem::updateYear(int year)
{
    return updateWrapper<int>("year", year, m_year);
}

bool db::AudioItem::updateDuration(int duration)
{
    return updateWrapper<int>("duration", duration, m_duration);
}

bool db::AudioItem::updateCoverId(int coverId)
{
    return updateWrapper<int>("coverid", coverId, m_coverId);
}

bool db::AudioItem::updateModified(qint64 modified)
{
    return updateWrapper<qint64>("modified", modified, m_modified);
}

void db::AudioItem::assignTo(Audio &audio) const
{
    audio.setFile(m_file);
    audio.tag().setTitle(m_title);
    audio.tag().setArtist(m_artist);
    audio.tag().setAlbum(m_album);
    audio.tag().setGenre(m_genre);
    audio.tag().setYear(m_year);
    audio.tag().setTrack(m_track);
    audio.duration().setSecs(m_duration);
    audio.cover().setId(m_coverId);
    audio.setModified(m_modified);
}

void db::AudioItem::loadFrom(const Audio &audio)
{
    m_file = audio.file();
    m_title = audio.tag().title();
    m_artist = audio.tag().artist();
    m_album = audio.tag().album();
    m_genre = audio.tag().genre();
    m_year = audio.tag().year();
    m_track = audio.tag().track();
    m_duration = audio.duration().secs();
    m_coverId = audio.cover().id();
    m_modified = audio.modified();
}

template<typename T>
bool db::AudioItem::updateWrapper(const QString &column, const T &value, T &member)
{
    if (update(column, value))
    {
        member = value;
        return true;
    }
    return false;
}

bool db::AudioItem::getBy(const QString &column, const QVariant &value)
{
    query().prepare(
        "SELECT * FROM audios "
        "WHERE " + column + " = :value"
    );
    query().bindValue(":value", value);

    if (!query().exec() || !query().first())
        return false;

    loadFromRecord(query().record());

    return true;
}

bool db::AudioItem::update(const QString &column, const QVariant &value)
{
    query().prepare(
        "UPDATE audios SET"
        "  " + column + " = :value "
        "WHERE file = :file"
    );
    query().bindValue(":file", m_file);
    query().bindValue(":value", value);

    return query().exec();
}

void db::AudioItem::loadFromRecord(const QSqlRecord &record)
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
