#include "audio.hpp"

using namespace TagLib;

Audio::Audio()
{

}

Audio::Audio(const QString &path)
{
    m_path = path;
    m_valid = readTags();

    // Use filename as title if tag is empty
    if (m_valid && m_title.isEmpty())
        m_title = FileUtil::fileName(m_path);
}

Audio::~Audio()
{

}

bool Audio::isValid() const
{
    return m_valid;
}

QString Audio::path() const
{
    return m_path;
}

QString Audio::title() const
{
    return m_title;
}

QString Audio::artist() const
{
    return m_artist;
}

QString Audio::album() const
{
    return m_album;
}

QString Audio::genre() const
{
    return m_genre;
}

int Audio::year() const
{
    return m_year;
}

int Audio::track() const
{
    return m_track;
}

int Audio::length() const
{
    return m_length;
}

QUrl Audio::url() const
{
    return QUrl::fromLocalFile(m_path);
}

int Audio::seconds() const
{
    return m_length % 60;
}

int Audio::minutes() const
{
    return (m_length - seconds()) / 60;
}

QPixmap Audio::cover(int size)
{
    return resizeCover(readCover(), size);
}

bool Audio::readTags()
{
    FileRef fileRef(m_path.toLatin1().data());

    if (fileRef.isNull() || !fileRef.tag() || !fileRef.audioProperties())
        return false;

    Tag *tag = fileRef.tag();
    AudioProperties *audioProp = fileRef.audioProperties();

    m_title = QString(tag->title().toCString());
    m_artist = QString(tag->artist().toCString());
    m_album = QString(tag->album().toCString());
    m_genre = QString(tag->genre().toCString());
    m_year = tag->year();
    m_track = tag->track();
    m_length = audioProp->length();

    return true;
}

QPixmap Audio::resizeCover(const QPixmap &cover, int size)
{
    return cover.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QPixmap Audio::readCover()
{
    MPEG::File file(m_path.toLatin1().data());
    ID3v2::Tag *tag = file.ID3v2Tag();

    if (tag)
    {
        ID3v2::FrameList frameList = tag->frameListMap()["APIC"];
        if (!frameList.isEmpty())
        {
            ID3v2::AttachedPictureFrame *frame = static_cast<ID3v2::AttachedPictureFrame *>(frameList.front());

            QPixmap image;
            image.loadFromData((const uchar *) frame->picture().data(), frame->picture().size());

            if (!image.isNull())
                return image;
        }
    }
    return QPixmap(IMG_DEFAULT_COVER);
}
