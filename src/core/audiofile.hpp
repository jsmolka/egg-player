#ifndef AUDIOFILE_HPP
#define AUDIOFILE_HPP

#include <QImage>
#include <QString>

#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <src/constants/path.hpp>

class AudioFile
{
public:
    explicit AudioFile(QString path);

    bool isValid() const;
    QString path() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;
    quint32 year() const;
    quint32 track() const;
    quint32 length() const;
    quint32 bitrate() const;
    QImage image() const;

    quint32 seconds() const;
    quint32 minutes() const;

private:
    bool readTags();
    bool readAudio();
    bool readImage();

    TagLib::FileRef m_ref;
    bool m_isValid;
    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    quint32 m_year;
    quint32 m_track;
    quint32 m_length;
    quint32 m_bitrate;
    QImage m_image;
};

#endif // AUDIOFILE_HPP
