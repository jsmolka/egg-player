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

    EGG_C_PROP(QString, file, setFile, file)
    EGG_C_PROP(QString, title, setTitle, title)
    EGG_C_PROP(QString, artist, setArtist, artist)
    EGG_C_PROP(QString, album, setAlbum, album)
    EGG_C_PROP(QString, genre, setGenre, genre)
    EGG_P_PROP(int, year, setYear, year)
    EGG_P_PROP(int, track, setTrack, track)
    EGG_P_PROP(int, duration, setDuration, duration)
    EGG_P_PROP(int, coverId, setCoverId, coverId)
    EGG_P_PROP(qint64, modified, setModified, modified)

    bool exists() override;
    bool insert() override;
    bool commit() override;

    bool createTable() override;

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

    void assignTo(Audio &audio) const;
    void loadFrom(const Audio &audio);

private:
    template <typename T>
    bool updateWrapper(const QString &column, const T &value, T &member);

    bool getBy(const QString &column, const QVariant &value) override;
    bool update(const QString &column, const QVariant &value) override;
    void loadFromRecord(const QSqlRecord &record) override;
};

}

#endif // DB_AUDIOITEM_HPP
