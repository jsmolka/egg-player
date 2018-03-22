#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <QImage>
#include <QString>
#include <QStringList>
#include <QUrl>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include <src/constants/path.hpp>
#include <src/utils/fileutil.hpp>

class Audio
{
public:
    Audio(QString path);

    bool isValid() const;
    QString path() const;
    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;
    quint32 year() const;
    quint32 track() const;
    quint32 length() const;

    quint32 seconds() const;
    quint32 minutes() const;
    QUrl url() const;
    QImage cover();

private:
    bool readTags();
    QImage resizeCover(QImage image);
    QImage getCover();
    QImage readCover();
    QImage loadCoverFromFile();

    bool m_isValid;
    QString m_path;
    QString m_title;
    QString m_artist;
    QString m_album;
    QString m_genre;
    quint32 m_year;
    quint32 m_track;
    quint32 m_length;
};

#endif // AUDIO_HPP
