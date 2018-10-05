#ifndef TAG_HPP
#define TAG_HPP

#include <QString>
#include <QPixmap>

#include "types.hpp"

class Tag : public QObject
{
    Q_OBJECT

public:    
    explicit Tag(QObject *parent = nullptr);
    explicit Tag(const File &file, QObject *parent = nullptr);

    bool read();

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

private:
    File m_file;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    int m_year;
    int m_track;
    int m_duration;
};

#endif // TAG_HPP
