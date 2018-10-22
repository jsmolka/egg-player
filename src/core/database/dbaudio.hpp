#ifndef DBAUDIO_HPP
#define DBAUDIO_HPP

#include "dbtableitem.hpp"
#include "globals.hpp"
#include "types.hpp"

class DbAudio : public DbTableItem
{
public:
    using DbTableItem::DbTableItem;

    EGG_CPROP(File, file, setFile, file)
    EGG_CPROP(QString, title, setTitle, title)
    EGG_CPROP(QString, artist, setArtist, artist)
    EGG_CPROP(QString, album, setAlbum, album)
    EGG_CPROP(QString, genre, setGenre, genre)
    EGG_PPROP(int, year, setYear, year)
    EGG_PPROP(int, track, setTrack, track)
    EGG_PPROP(int, duration, setDuration, duration)
    EGG_PPROP(int, coverId, setCoverId, coverId)
    EGG_PPROP(qint64, modified, setModified, modified)

    bool insert();
    bool commit();
    bool updatePrimaryKey(const File &file);

    bool getBy(const QVariant &column, const QVariant &value);
    bool getByFile(const File &file);
    bool getByTitle(const QString &title);
};

#endif // DBAUDIO_HPP
