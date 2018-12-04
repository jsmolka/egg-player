#ifndef DB_AUDIOITEM_HPP
#define DB_AUDIOITEM_HPP

#include "core/audio.hpp"
#include "core/macros.hpp"
#include "core/database/tableitem.hpp"

namespace db
{

class AudioItem : public TableItem
{
public:
    AudioItem();

    EGG_CPROP(QString, file, setFile, file)
    EGG_CPROP(QString, title, setTitle, title)
    EGG_CPROP(QString, artist, setArtist, artist)
    EGG_CPROP(QString, album, setAlbum, album)
    EGG_CPROP(QString, genre, setGenre, genre)
    EGG_PPROP(int, year, setYear, year)
    EGG_PPROP(int, track, setTrack, track)
    EGG_PPROP(int, duration, setDuration, duration)
    EGG_PPROP(int, coverId, setCoverId, coverId)
    EGG_PPROP(qint64, modified, setModified, modified)

    bool exists();
    bool insert();
    bool commit();

    bool createTable();

    bool getByFile(const QString &file);
    bool getByTitle(const QString &title);
    bool getByAlbum(const QString &album);
    bool getByArtist(const QString &artist);
    bool getByYear(int year);
    bool getByDuration(int duration);
    bool getByCoverId(int coverId);
    bool getByModified(qint64 modified);

    bool updateFile(const QString &file);
    bool updateTitle(const QString &title);
    bool updateAlbum(const QString &album);
    bool updateArtist(const QString &artist);
    bool updateYear(int year);
    bool updateDuration(int duration);
    bool updateCoverId(int coverId);
    bool updateModified(qint64 modified);

    void assignTo(Audio &audio);
    void loadFrom(const Audio &audio);

protected:
    bool getBy(const QString &column, const QVariant &value);
    bool update(const QString &column, const QVariant &value);

private:
    void loadFromRecord(const QSqlRecord &record);
};

}

#endif // DB_AUDIOITEM_HPP
