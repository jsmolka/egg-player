#ifndef AUDIOFILE_HPP
#define AUDIOFILE_HPP

#include <QImage>
#include <QString>
#include <QStringList>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include <src/constants/path.hpp>
#include <src/utils/fileutil.hpp>

using namespace TagLib;

class AudioFile
{
public:
    AudioFile(QString path, bool autoLoadCover = true);

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

    void setCover(QImage cover);
    QImage cover() const;

    void setCoverPtr(QImage *coverPtr);
    QImage * coverPtr() const;

    quint32 seconds() const;
    quint32 minutes() const;

    QImage getCover();

private:
    bool readTags();
    bool readAudio();
    QImage readCover();
    QImage loadCoverFromFile();

    FileRef m_ref;
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
    QImage m_cover;
    QImage *m_coverPtr;
};

#endif // AUDIOFILE_HPP
