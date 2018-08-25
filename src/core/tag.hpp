#ifndef TAG_HPP
#define TAG_HPP

#include <QString>
#include <QPixmap>

#include <taglib/mpegfile.h>

class Tag
{
public:
    explicit Tag(const wchar_t *file);

    bool isValid() const;
    bool isAudioValid() const;
    bool isTagValid() const;

    QString title() const;
    QString artist() const;
    QString album() const;
    QString genre() const;

    int year() const;
    int track() const;
    int duration() const;

    QPixmap cover();

private:
    static QString toQString(const TagLib::String &string);
    static QString toQString(const TagLib::FileName &string);

    TagLib::MPEG::File m_file;
};

#endif // TAG_HPP
