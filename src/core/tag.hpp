#ifndef TAG_HPP
#define TAG_HPP

#include <QString>
#include <QPainter>
#include <QPixmap>

#include <taglib/attachedpictureframe.h>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/id3v2frame.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

#include "duration.hpp"
#include "logger.hpp"
#include "util.hpp"

class Tag
{
public:
    Tag(const wchar_t *file);
    ~Tag();

    bool isValid() const;
    bool isAudioValid() const;
    bool isTagValid() const;

    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;
    int year() const;
    int track() const;
    Duration duration() const;

    QPixmap cover(int size);

private:
    QPixmap coverify(const QPixmap &cover);
    QPixmap readCover();

    QString toQString(const TagLib::String &string) const;

    TagLib::MPEG::File m_file;
};

#endif // TAG_HPP
