#ifndef TAG_HPP
#define TAG_HPP

#include <QString>
#include <QPixmap>

#include <taglib/fileref.h>

#include "duration.hpp"
#include "types.hpp"

class Tag : public QObject
{
    Q_OBJECT

public:    
    explicit Tag(QObject *parent = nullptr);
    explicit Tag(const File &file, QObject *parent = nullptr);

    bool readTag();
    QPixmap readCover();

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

    void setDuration(int secs);
    void setDuration(const Duration &duration);
    Duration duration() const;

signals:
    void updated();

private:
    static const wchar_t *toWString(const QString &string);
    static QString toQString(const TagLib::String &string);
    static QString toQString(const TagLib::FileName &string);

private:
    File m_file;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    int m_year;
    int m_track;
    Duration m_duration;
};

#endif // TAG_HPP
