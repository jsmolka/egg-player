#ifndef DBAUDIO_HPP
#define DBAUDIO_HPP

#include "dbtableitem.hpp"
#include "types.hpp"

class DbAudio : public DbTableItem
{
public:
    using DbTableItem::DbTableItem;

    void setFile(const File &file);
    File file() const;

    void setTitle(const QString &title);
    QString title() const;

    void setArtist(const QString &artist);
    QString artist() const;

    void setAlbum(const QString &album);
    QString album() const;

    void setGenre(const QString &genre);
    QString genre() const;

    void setYear(int year);
    int year() const;

    void setTrack(int track);
    int track() const;

    void setDuration(int duration);
    int duration() const;

    void setCoverId(int id);
    int coverId() const;

    void setModified(qint64 modified);
    qint64 modified() const;

    bool insert();
    bool commit();

    bool getBy(const QVariant &column, const QVariant &value);
    bool getByFile(const File &file);
    bool getByTitle(const QString &title);

private:
    File m_file;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    int m_year;
    int m_track;
    int m_duration;
    int m_coverId;
    qint64 m_modified;
};

#endif // DBAUDIO_HPP
