#ifndef DBAUDIO_HPP
#define DBAUDIO_HPP

#include "audio.hpp"
#include "dbtableitem.hpp"
#include "globals.hpp"

class DbAudio : public DbTableItem
{
public:
    using DbTableItem::DbTableItem;

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
    bool updatePrimaryKey(const QString &file);

    bool getByFile(const QString &file);
    bool getByTitle(const QString &title);

    void assign(Audio *audio);
    void load(Audio *audio);

protected:
    bool getBy(const QVariant &column, const QVariant &value);
};

#endif // DBAUDIO_HPP
